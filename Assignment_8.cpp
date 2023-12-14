#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

// Function to perform right rotation
inline uint32_t rightRotate(uint32_t element_value, int shift_across) {
    return (element_value >> shift_across) | (element_value << (32 - shift_across));
}

// SHA-256 Compression function
void sha256Compress(std::vector<uint32_t>& hash_value, const std::vector<uint32_t>& k, const std::vector<uint32_t>& w) {
    for (int i = 0; i < 64; ++i) {
        uint32_t s1_value = rightRotate(hash_value[4], 6) ^ rightRotate(hash_value[4], 11) ^ rightRotate(hash_value[4], 25);
        uint32_t ch_value = (hash_value[4] & hash_value[5]) ^ (~hash_value[4] & hash_value[6]);
        uint32_t temp1_value = hash_value[7] + s1_value + ch_value + k[i] + w[i];
        uint32_t s0_value = rightRotate(hash_value[0], 2) ^ rightRotate(hash_value[0], 13) ^ rightRotate(hash_value[0], 22);
        uint32_t maj_value = (hash_value[0] & hash_value[1]) ^ (hash_value[0] & hash_value[2]) ^ (hash_value[1] & hash_value[2]);
        uint32_t temp2_value = s0_value + maj_value;

        hash_value[7] = hash_value[6];
        hash_value[6] = hash_value[5];
        hash_value[5] = hash_value[4];
        hash_value[4] = (hash_value[3] + temp1_value) % UINT32_MAX;
        hash_value[3] = hash_value[2];
        hash_value[2] = hash_value[1];
        hash_value[1] = hash_value[0];
        hash_value[0] = (temp1_value + temp2_value) % UINT32_MAX;
    }
}

// SHA-256 Hash function
std::vector<uint32_t> sha256(const std::string& message_url) {
    std::vector<uint32_t> hash_values = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };

    std::vector<uint32_t> k_values = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
        0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
        0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
        0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
        0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
        0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
        0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
        0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
        0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };

    // Pre-processing (Padding)
    uint64_t original_message_Length = message_url.length() * 8;
    std::string padded_url_Message = message_url + static_cast<char>(0x80);
    while (padded_url_Message.length() % 64 != 56) {
        padded_url_Message += static_cast<char>(0x00);
    }
    for (int element = 7; element >= 0; --element) {
        padded_url_Message += static_cast<char>((original_message_Length >> (element * 8)) & 0xFF);
    }

    // Process the message in successive 512-bit chunks
    for (size_t element = 0; element < padded_url_Message.length(); element += 64) {
        std::vector<uint32_t> w(64, 0);
        for (int value = 0; value < 16; ++value) {
            w[value] = (static_cast<uint32_t>(padded_url_Message[element + value * 4]) << 24) |
                   (static_cast<uint32_t>(padded_url_Message[element + value * 4 + 1]) << 16) |
                   (static_cast<uint32_t>(padded_url_Message[element + value * 4 + 2]) << 8) |
                   static_cast<uint32_t>(padded_url_Message[element + value * 4 + 3]);
        }

        for (int value = 16; value < 64; ++value) {
            uint32_t s0 = rightRotate(w[value - 15], 7) ^ rightRotate(w[value - 15], 18) ^ (w[value - 15] >> 3);
            uint32_t s1 = rightRotate(w[value - 2], 17) ^ rightRotate(w[value - 2], 19) ^ (w[value - 2] >> 10);
            w[value] = (w[value - 16] + s0 + w[value - 7] + s1) % UINT32_MAX;
        }

        sha256Compress(hash_values, k_values, w);
    }

    return hash_values;
}

// Convert hash to hexadecimal string
std::string hashToHexString(const std::vector<uint32_t>& hash) {
    std::ostringstream oss;
    for (const auto& value : hash) {
        oss << std::hex << std::setw(8) << std::setfill('0') << value;
    }
    return oss.str();
}

// Function to fetch content from a given URL
std::string fetchContent(const std::string& host, const std::string& path) {
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        std::cerr << "Error opening socket" << std::endl;
        return "";
    }

    struct hostent* server_get = gethostbyname(host.c_str());
    if (server_get == nullptr) {
        std::cerr << "Error, no such host" << std::endl;
        return "";
    }

    struct sockaddr_in serverAddress_value;
    std::memset(&serverAddress_value, 0, sizeof(serverAddress_value));
    serverAddress_value.sin_family = AF_INET;
    serverAddress_value.sin_port = htons(80);
    std::memcpy(&serverAddress_value.sin_addr.s_addr, server_get->h_addr, server_get->h_length);

    if (connect(sock_fd, (struct sockaddr*)&serverAddress_value, sizeof(serverAddress_value)) < 0) {
        std::cerr << "Error connecting" << std::endl;
        return "";
    }

    std::string request = "GET " + path + " HTTP/1.1\r\nHost: " + host + "\r\nConnection: close\r\n\r\n";
    if (send(sock_fd, request.c_str(), request.length(), 0) < 0) {
        std::cerr << "Error sending request" << std::endl;
        return "";
    }

    std::ostringstream response_received;
    char buffer_value[1024];
    ssize_t bytesRead_value;
    while ((bytesRead_value = recv(sock_fd, buffer_value, sizeof(buffer_value), 0)) > 0) {
        response_received.write(buffer_value, bytesRead_value);
    }

    close(sock_fd); // Close the socket

    return response_received.str();
}

int main() {
    // Example usage
    std::string host_taken = "quod.lib.umich.edu";
    // std::string host_taken = "en.wikipedia.org";
    std::string path_taken = "/cgi/r/rsv/rsv-idx?type=DIV1&byte=4697892";
    // std::string path_taken = "/wiki/Wiki";
    std::string content_received = fetchContent(host_taken, path_taken);

    if (!content_received.empty()) {
        std::vector<uint32_t> hash_value = sha256(content_received);
        std::string hashedResult_value = hashToHexString(hash_value);
        std::cout << "Hashed content: " << hashedResult_value << std::endl;
    } else {
        std::cerr << "Unable to fetch content from the URL" << std::endl;
    }

    return 0;
}
