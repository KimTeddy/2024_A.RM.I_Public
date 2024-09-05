#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "json.hpp"
#include "main.hpp"
#include "uart.hpp"

char hex_string[32767] = { 0 };

// Define a structure to store detection results
struct detectionResult
{
    cv::Rect plateRect;
    double confidence;
    int type;
};

// Function to load class names from a JSON file
std::map<int, std::string> loadClassNames(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }

    nlohmann::json j;
    file >> j;

    std::map<int, std::string> classNames;
    const auto& classData = j["class"];
    for (auto it = classData.begin(); it != classData.end(); ++it) {
        int key = std::stoi(it.key());
        std::string value = it.value();
        classNames[key] = value;
    }

    return classNames;
}

int main() {
    // COM 포트 열기/시리얼 포트 설정/타임아웃 설정
    UART_init(UART_DECLINE_ERROR);
    while (1)
        if (UART_read(hex_string) == 0) break;

    long binary_length;
    unsigned char* binary_data = hex_string_to_binary(hex_string, &binary_length);
    printf("1\n");

    if (!binary_data) {
        return 1;
    }
    printf("2\n");

    // 바이너리 데이터를 JPEG 파일로 저장
    FILE* output_file;
    if (fopen_s(&output_file, "1.jpg", "wb") != 0) {
        fprintf(stderr, "JPEG 파일 열기 실패\n");
        free(binary_data);
        return 1;
    }
    printf("3\n");

    fwrite(binary_data, 1, binary_length, output_file);
    fclose(output_file);

    printf("이미지가 성공적으로 저장되었습니다: 1.jpg\n");
    free(binary_data);

    // Load class names from the JSON file
    std::map<int, std::string> classNames = loadClassNames("./yolo/yolo_classes.json");

    // Read the image
    cv::Mat img = cv::imread("1.jpg");
    if (img.empty()) {
        std::cerr << "Error reading image" << std::endl;
        return -1;
    }

    // Initialize YOLO network
    using namespace cv::dnn;
    const float confidenceThreshold = 0.24f;
    Net m_net;
    std::string yolo_cfg = "./yolo/yolov4.cfg";
    std::string yolo_weights = "./yolo/yolov4.weights";
    m_net = readNetFromDarknet(yolo_cfg, yolo_weights);
    m_net.setPreferableBackend(DNN_BACKEND_OPENCV);
    m_net.setPreferableTarget(DNN_TARGET_CPU);

    // Prepare the image for the network
    cv::Mat inputBlob = blobFromImage(img, 1 / 255.F, cv::Size(416, 416), cv::Scalar(), true, false);

    m_net.setInput(inputBlob);

    // Forward pass
    std::vector<cv::Mat> outs;
    m_net.forward(outs, m_net.getUnconnectedOutLayersNames());

    std::vector<detectionResult> vResultRect;

    // Process the detections
    for (const auto& detectionMat : outs) {
        for (int i = 0; i < detectionMat.rows; i++) {
            const int probability_index = 5;
            const int probability_size = detectionMat.cols - probability_index;

            // Use const_cast to convert const float* to float*
            float* prob_array_ptr = const_cast<float*>(detectionMat.ptr<float>(i) + probability_index);

            size_t objectClass = std::max_element(prob_array_ptr, prob_array_ptr + probability_size) - prob_array_ptr;
            float confidence = detectionMat.at<float>(i, (int)objectClass + probability_index);
            if (confidence > confidenceThreshold) {
                float x_center = detectionMat.at<float>(i, 0) * (float)img.cols;
                float y_center = detectionMat.at<float>(i, 1) * (float)img.rows;
                float width = detectionMat.at<float>(i, 2) * (float)img.cols;
                float height = detectionMat.at<float>(i, 3) * (float)img.rows;
                cv::Point2i p1(round(x_center - width / 2.f), round(y_center - height / 2.f));
                cv::Point2i p2(round(x_center + width / 2.f), round(y_center + height / 2.f));
                cv::Rect2i object(p1, p2);

                detectionResult tmp;
                tmp.plateRect = object;
                tmp.confidence = confidence;
                tmp.type = objectClass;
                vResultRect.push_back(tmp);
            }
        }
    }

    // Apply Non-Maximum Suppression
    NMS(vResultRect);

    // Draw bounding boxes and labels
    for (const auto& result : vResultRect) {
        cv::rectangle(img, result.plateRect, cv::Scalar(0, 0, 255), 2);
        std::string label = classNames[result.type] + ": " + std::to_string(result.confidence);
        cv::putText(img, label, result.plateRect.tl(), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 2);
    }

    // Show the result


    resize(img, img, cv::Size(320*5, 240*5));
    cv::imshow("img", img);
    cv::waitKey();

    return 0;
}

void NMS(std::vector<detectionResult>& vResultRect) {
    for (int i = 0; i < vResultRect.size() - 1; i++) {
        for (int j = i + 1; j < vResultRect.size(); j++) {
            double IOURate = (double)(vResultRect[i].plateRect & vResultRect[j].plateRect).area() / (vResultRect[i].plateRect | vResultRect[j].plateRect).area();
            if (IOURate >= 0.5) {
                if (vResultRect[i].confidence > vResultRect[j].confidence) {
                    vResultRect.erase(vResultRect.begin() + j);
                    j--;
                }
                else {
                    vResultRect.erase(vResultRect.begin() + i);
                    i--;
                    break;
                }
            }
        }
    }
}

// 16진수 문자열을 바이너리 데이터로 변환하는 함수
unsigned char hex_char_to_byte(char hex_char) {
    if (hex_char >= '0' && hex_char <= '9') {
        return hex_char - '0';
    }
    else if (hex_char >= 'A' && hex_char <= 'F') {
        return hex_char - 'A' + 10;
    }
    else if (hex_char >= 'a' && hex_char <= 'f') {
        return hex_char - 'a' + 10;
    }
    else {
        fprintf(stderr, "유효하지 않은 16진수 문자: %c\n", hex_char);
        return 0;
    }
}

// 텍스트 파일에서 16진수 문자열을 읽어오는 함수
char* read_hex_string_from_file(const char* filename) {
    FILE* file;
    if (fopen_s(&file, filename, "r") != 0) {
        fprintf(stderr, "파일 열기 실패: %s\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* hex_string = (char*)malloc(length + 1);
    if (!hex_string) {
        fprintf(stderr, "메모리 할당 실패\n");
        fclose(file);
        return NULL;
    }

    fread(hex_string, 1, length, file);
    hex_string[length] = '\0'; // null 문자 추가
    fclose(file);

    return hex_string;
}

// 16진수 문자열을 바이너리 데이터로 변환하는 함수
unsigned char* hex_string_to_binary(const char* hex_string, long* binary_length) {
    long hex_length = strlen(hex_string);
    if (hex_length % 2 != 0) {
        fprintf(stderr, "16진수 문자열의 길이가 짝수가 아닙니다.\n");
        return NULL;
    }

    *binary_length = hex_length / 2;
    unsigned char* binary_data = (unsigned char*)malloc(*binary_length);
    if (!binary_data) {
        fprintf(stderr, "메모리 할당 실패\n");
        return NULL;
    }

    for (long i = 0; i < *binary_length; i++) {
        binary_data[i] = (hex_char_to_byte(hex_string[i * 2]) << 4) | hex_char_to_byte(hex_string[i * 2 + 1]);
    }

    return binary_data;
}