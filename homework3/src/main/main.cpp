#include "serializer/serializer.hpp"

int main() 
{
    pkg::S1 s1_1 {1}, s1_2 {2}, s1_3 {3};
    pkg::S2 s2_1 {1.23f};
    pkg::S3 s3_struct = pkg::S3 { 323, "example_string", {1, 2, 3}, s2_1, {s1_1, s1_2, s1_3} };

    nlohmann::json j = serialize(s3_struct);
    std::cout << "Serialized JSON:\n" << j.dump(4) << std::endl;

    pkg::S3 deserialized_s3 = deserialize<pkg::S3>(j);
    std::cout << "\nDeserialized structure:\n";
    std::cout << "r1: " << deserialized_s3.r1 << "\n";
    std::cout << "some_str: " << deserialized_s3.some_str << "\n";
    std::cout << "vals: ";
    for (int val : deserialized_s3.vals) {
        std::cout << val << " ";
    }
    std::cout << "\ns2_val.val: " << deserialized_s3.s2_val.val << "\n";
    std::cout << "s1_vals:\n";
    for (const auto& s1 : deserialized_s3.s1_vals) {
        std::cout << "  r0: " << s1.r0 << "\n";
    }
}