#include <iostream>
#include <curl/curl.h>
#include <string>
#include <json/json.h>

// Callback function to receive data from cURL
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t total_size = size * nmemb;
    output->append((char*)contents, total_size);
    return total_size;
}

// Function to get cryptocurrency price
std::string getCryptoPrice(const std::string& crypto, const std::string& currency) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://api.coingecko.com/api/v3/simple/price?ids=" + crypto + "&vs_currencies=" + currency;
        
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            std::cerr << "cURL request failed: " << curl_easy_strerror(res) << std::endl;
            return "";
        }
    }

    return readBuffer;
}

int main() {
    std::string crypto, currency;

    std::cout << "Enter cryptocurrency (e.g., bitcoin, ethereum): ";
    std::cin >> crypto;
    std::cout << "Enter currency (e.g., usd, eur): ";
    std::cin >> currency;

    std::string jsonResponse = getCryptoPrice(crypto, currency);

    if (!jsonResponse.empty()) {
        Json::Value jsonData;
        Json::Reader reader;

        if (reader.parse(jsonResponse, jsonData)) {
            std::cout << "Current price of " << crypto << " in " << currency << ": " 
                      << jsonData[crypto][currency].asFloat() << std::endl;
        } else {
            std::cerr << "Failed to parse JSON response!" << std::endl;
        }
    } else {
        std::cerr << "Failed to fetch cryptocurrency data!" << std::endl;
    }

    return 0;
}