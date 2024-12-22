#include "../../main/serializer/serializer.hpp"

class TestSerializer {
    static void testSerializeS1()
    {
        pkg::S1 s1_1 { 1 };

        nlohmann::json j = serialize(s1_1);

        assert(j["r0"] == 1);
    }

    static void testDeserializeS1()
    {
        pkg::S1 s1_1 { 1 };

        nlohmann::json j = serialize(s1_1);
        pkg::S1 deserialized_s1 = deserialize<pkg::S1>(j);

        assert(deserialized_s1.r0 == 1);
    }

    static void testSerializeS2()
    {
        pkg::S2 s2_1 { 1.23f };

        nlohmann::json j = serialize(s2_1);

        assert(j["val"] == 1.23f);
    }

    static void testDeserializeS2()
    {
        pkg::S2 s2_1 { 1.23f };

        nlohmann::json j = serialize(s2_1);
        pkg::S2 deserialized_s2 = deserialize<pkg::S2>(j);

        assert(deserialized_s2.val == 1.23f);
    }

    static void testSerializeS3()
    {
        pkg::S1 s1_1 { 1 }, s1_2 { 2 }, s1_3 { 3 };
        pkg::S2 s2_1 { 1.23f };
        pkg::S3 s3_struct = pkg::S3 { 42, "example_string", { 1, 2, 3 }, s2_1, { s1_1, s1_2, s1_3 } };

        nlohmann::json j = serialize(s3_struct);

        assert(j["r1"] == 42);
        assert(j["some_str"] == "example_string");
        assert(j["vals"] == std::vector<int>({ 1, 2, 3 }));
        assert(j["s2_val"]["val"] == 1.23f);
        assert(j["s1_vals"].size() == 3);
        assert(j["s1_vals"][0]["r0"] == 1);
        assert(j["s1_vals"][1]["r0"] == 2);
        assert(j["s1_vals"][2]["r0"] == 3);
    }

    static void testDeserializeS3()
    {
        pkg::S1 s1_1 { 1 }, s1_2 { 2 }, s1_3 { 3 };
        pkg::S2 s2_1 { 1.23f };
        pkg::S3 s3_struct = pkg::S3 { 42, "example_string", { 1, 2, 3 }, s2_1, { s1_1, s1_2, s1_3 } };

        nlohmann::json j = serialize(s3_struct);
        pkg::S3 deserialized_s3 = deserialize<pkg::S3>(j);

        assert(deserialized_s3.r1 == 42);
        assert(deserialized_s3.some_str == "example_string");
        assert(deserialized_s3.vals == std::vector<int>({ 1, 2, 3 }));
        assert(deserialized_s3.s2_val.val == 1.23f);
        assert(deserialized_s3.s1_vals.size() == 3);
        assert(deserialized_s3.s1_vals[0].r0 == 1);
        assert(deserialized_s3.s1_vals[1].r0 == 2);
        assert(deserialized_s3.s1_vals[2].r0 == 3);
    }

public:
    static void runTests()
    {
        testSerializeS1();
        testDeserializeS1();
        testSerializeS2();
        testDeserializeS2();
        testSerializeS3();
        testDeserializeS3();

        std::cout << "All tests passed!" << std::endl;
    }
};

int main()
{
    TestSerializer::runTests();
}