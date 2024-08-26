#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <bitset>
#include <sstream>

class ByteNode {
public:
    ByteNode *left;
    ByteNode *right;
    int frequency;
    std::optional<char> data;

    ByteNode(char data, int frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
    ByteNode(int frequency) : frequency(frequency), left(nullptr), right(nullptr) {}

    bool operator>(const ByteNode &other) const {
        return frequency > other.frequency;
    }
};

class MinPriorityQueue {
    std::priority_queue<ByteNode*, std::vector<ByteNode*>, std::greater<ByteNode*>> pq;

public:
    void add(ByteNode *node) {
        pq.push(node);
    }

    ByteNode *poll() {
        ByteNode *top = pq.top();
        pq.pop();
        return top;
    }

    int len() const {
        return pq.size();
    }
};

class HuffCompression {
private:
    std::string sb;
    std::unordered_map<char, std::string> huffmap;

    MinPriorityQueue getByteNodes(const std::vector<char> &bytes) {
        MinPriorityQueue nodes;
        std::unordered_map<char, int> tempMap;
        for (char b : bytes) {
            tempMap[b]++;
        }
        for (const auto &entry : tempMap) {
            nodes.add(new ByteNode(entry.first, entry.second));
        }
        return nodes;
    }

    ByteNode *createHuffmanTree(MinPriorityQueue &nodes) {
        while (nodes.len() > 1) {
            ByteNode *left = nodes.poll();
            ByteNode *right = nodes.poll();
            ByteNode *parent = new ByteNode(left->frequency + right->frequency);
            parent->left = left;
            parent->right = right;
            nodes.add(parent);
        }
        return nodes.poll();
    }

    void getHuffCodes(ByteNode *node, const std::string &code) {
        if (node) {
            if (!node->data.has_value()) {
                getHuffCodes(node->left, code + "0");
                getHuffCodes(node->right, code + "1");
            } else {
                huffmap[node->data.value()] = code;
            }
        }
    }

    std::vector<char> zipBytesWithCodes(const std::vector<char> &bytes, const std::unordered_map<char, std::string> &huffCodes) {
        std::stringstream strBuilder;
        for (char b : bytes) {
            strBuilder << huffCodes.at(b);
        }

        std::string bits = strBuilder.str();
        int length = (bits.size() + 7) / 8;
        std::vector<char> huffCodeBytes(length);

        int idx = 0;
        for (size_t i = 0; i < bits.size(); i += 8) {
            std::string strByte = bits.substr(i, 8);
            if (strByte.size() < 8) {
                strByte.append(8 - strByte.size(), '0');
            }
            huffCodeBytes[idx++] = static_cast<char>(std::bitset<8>(strByte).to_ulong());
        }
        return huffCodeBytes;
    }

    std::string convertByteInBit(bool flag, char b) {
        int byte0 = static_cast<unsigned char>(b);
        if (flag) byte0 |= 256;
        std::string str0 = std::bitset<9>(byte0).to_string();
        if (flag || byte0 < 0) {
            return str0.substr(str0.size() - 8);
        } else {
            return str0;
        }
    }

public:
    void compress(const std::string &src, const std::string &dst) {
        std::ifstream inStream(src, std::ios::binary);
        std::vector<char> bytes((std::istreambuf_iterator<char>(inStream)), std::istreambuf_iterator<char>());

        std::vector<char> huffmanBytes = createZip(bytes);

        std::ofstream outStream(dst, std::ios::binary);
        std::ofstream objectOutStream(dst + ".map", std::ios::binary);
        outStream.write(huffmanBytes.data(), huffmanBytes.size());

        for (const auto &pair : huffmap) {
            objectOutStream << pair.first << ' ' << pair.second << '\n';
        }
    }

    std::vector<char> createZip(const std::vector<char> &bytes) {
        MinPriorityQueue nodes = getByteNodes(bytes);
        ByteNode *root = createHuffmanTree(nodes);
        getHuffCodes(root, "");
        return zipBytesWithCodes(bytes, huffmap);
    }

    void decompress(const std::string &src, const std::string &dst) {
        std::ifstream inStream(src, std::ios::binary);
        std::ifstream objectInStream(src + ".map", std::ios::binary);

        std::vector<char> huffmanBytes((std::istreambuf_iterator<char>(inStream)), std::istreambuf_iterator<char>());

        std::unordered_map<char, std::string> huffmanCodes;
        char key;
        std::string value;
        while (objectInStream >> key >> value) {
            huffmanCodes[key] = value;
        }

        std::vector<char> bytes = decomp(huffmanCodes, huffmanBytes);

        std::ofstream outStream(dst, std::ios::binary);
        outStream.write(bytes.data(), bytes.size());
    }

    std::vector<char> decomp(const std::unordered_map<char, std::string> &huffmanCodes, const std::vector<char> &huffmanBytes) {
        std::stringstream sb1;
        for (size_t i = 0; i < huffmanBytes.size(); ++i) {
            sb1 << convertByteInBit(i != huffmanBytes.size() - 1, huffmanBytes[i]);
        }

        std::unordered_map<std::string, char> map;
        for (const auto &entry : huffmanCodes) {
            map[entry.second] = entry.first;
        }

        std::vector<char> result;
        for (size_t i = 0; i < sb1.str().size();) {
            int count = 1;
            bool flag = true;
            char b = 0;
            while (flag) {
                std::string key = sb1.str().substr(i, count);
                auto it = map.find(key);
                if (it != map.end()) {
                    b = it->second;
                    flag = false;
                } else {
                    count++;
                }
            }
            result.push_back(b);
            i += count;
        }
        return result;
    }
};

int main() {
    HuffCompression hc;
    hc.compress("input.txt", "compressed.huff");
    hc.decompress("compressed.huff", "output.txt");

    return 0;
}
