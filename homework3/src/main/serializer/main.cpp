#include <boost/fusion/adapted/struct/define_struct.hpp>
#include <boost/fusion/include/define_struct.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/transform.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/fusion/include/algorithm.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/transform.hpp>

#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include <iostream>

#define FIELD_NAME(field) #field

BOOST_FUSION_DEFINE_STRUCT(
    (pkg),
    S1,
    (int, r0)
)

BOOST_FUSION_DEFINE_STRUCT(
    (pkg),
    S2,
    (float, val)
)

BOOST_FUSION_DEFINE_STRUCT(
	(pkg),
	S3,
	(int, r1)
	(std::string, some_str)
    (std::vector<int>, vals)
    (pkg::S2, s2_val)
    (std::vector<pkg::S1>, s1_vals)
)

// Сериализация
template <typename T>
nlohmann::json serialize(const T& obj) {
    nlohmann::json j;

    // Используем Boost.Fusion для обхода структуры и преобразования в json
    boost::fusion::for_each(boost::mpl::range_c<unsigned, 0, boost::fusion::result_of::size<T>::value>(), [&](auto index) {
        auto field = boost::fusion::at_c<index>(obj);
        using FieldType = std::decay_t<decltype(field)>;
        std::string fieldName = boost::fusion::extension::struct_member_name<T, index>::call();

        // Если поле является вектором, сериализуем элементы по очереди
        if constexpr (std::is_same_v<FieldType, std::vector<int>>) {
            j[fieldName] = field;
        }
        else if constexpr (std::is_same_v<FieldType, std::vector<pkg::S1>>) {
            // Для вектора структур S1
            nlohmann::json arr = nlohmann::json::array();
            for (const auto& item : field) {
                arr.push_back({{"r0", item.r0}});
            }
            j[fieldName] = arr;
        }
        else if constexpr (std::is_same_v<FieldType, pkg::S2>) {
            j[fieldName] = {{"val", field.val}};
        }
        else if constexpr (std::is_same_v<FieldType, std::string>) {
            j[fieldName] = field;
        }
        else if constexpr (std::is_same_v<FieldType, int>) {
            j[fieldName] = field;  // Для поля r1
        }
        else if constexpr (std::is_same_v<FieldType, float>) {
            j[fieldName] = field;
        }
        else {
            // Для других полей
            j[fieldName] = field;
        }
    });

    return j;
}

// Десериализация
template <typename T>
T deserialize(const nlohmann::json& j) {
    T obj;

    // Используем Boost.Fusion для обхода структуры и присваивания значений из JSON
    boost::fusion::for_each(boost::mpl::range_c<unsigned, 0, boost::fusion::result_of::size<T>::value>(), [&](auto index) {
        auto& field = boost::fusion::at_c<index>(obj);
        using FieldType = std::decay_t<decltype(field)>;
        std::string fieldName = boost::fusion::extension::struct_member_name<T, index>::call();

        // Преобразуем вектора и другие поля из JSON
        if constexpr (std::is_same_v<FieldType, std::vector<int>>) {
            field = j[fieldName].get<std::vector<int>>();  // Преобразуем вектор из JSON
        }
        else if constexpr (std::is_same_v<FieldType, std::vector<pkg::S1>>) {
            // Для вектора структур S1
            for (const auto& item : j[fieldName]) {
                pkg::S1 s1_item;
                s1_item.r0 = item["r0"].get<int>();  // Извлекаем "r0"
                field.push_back(s1_item);
            }
        }
        else if constexpr (std::is_same_v<FieldType, pkg::S2>) {
            field.val = j[fieldName]["val"].get<float>();  // Извлекаем значение из s2_val
        }
        else if constexpr (std::is_same_v<FieldType, std::string>) {
            field = j[fieldName].get<std::string>();
        }
        else if constexpr (std::is_same_v<FieldType, int>) {
            field = j[fieldName].get<int>();  // Извлекаем значение для поля r1
        }
        else if constexpr (std::is_same_v<FieldType, float>) {
            field = j[fieldName].get<float>();
        }
        else {
            field = j[fieldName].get<decltype(field)>();
        }
    });

    return obj;
}

class TestSerializer
{
    static void testSerializeS1() {
        pkg::S1 s1_1 {1};

        nlohmann::json j = serialize(s1_1);

        assert(j["r0"] == 1);
    }

    static void testDeserializeS1() {
        pkg::S1 s1_1 {1};

        nlohmann::json j = serialize(s1_1);
        pkg::S1 deserialized_s1 = deserialize<pkg::S1>(j);

        // Проверка десериализации для S1
        assert(deserialized_s1.r0 == 1);
    }

    static void testSerializeS2() {
        pkg::S2 s2_1 {1.23f};

        nlohmann::json j = serialize(s2_1);

        // Проверка сериализации для S2
        assert(j["val"] == 1.23f);
    }

    static void testDeserializeS2() {
        pkg::S2 s2_1 {1.23f};

        nlohmann::json j = serialize(s2_1);
        pkg::S2 deserialized_s2 = deserialize<pkg::S2>(j);

        // Проверка десериализации для S2
        assert(deserialized_s2.val == 1.23f);
    }

    static void testSerializeS3() {
        pkg::S1 s1_1 {1}, s1_2 {2}, s1_3 {3};
        pkg::S2 s2_1 {1.23f};
        pkg::S3 s3_struct = pkg::S3 {42, "example_string", {1, 2, 3}, s2_1, {s1_1, s1_2, s1_3}};

        nlohmann::json j = serialize(s3_struct);

        // Проверка значений после сериализации
        assert(j["r1"] == 42);
        assert(j["some_str"] == "example_string");
        assert(j["vals"] == std::vector<int>({1, 2, 3}));
        assert(j["s2_val"]["val"] == 1.23f);
        assert(j["s1_vals"].size() == 3);
        assert(j["s1_vals"][0]["r0"] == 1);
        assert(j["s1_vals"][1]["r0"] == 2);
        assert(j["s1_vals"][2]["r0"] == 3);
    }

    static void testDeserializeS3() {
        pkg::S1 s1_1 {1}, s1_2 {2}, s1_3 {3};
        pkg::S2 s2_1 {1.23f};
        pkg::S3 s3_struct = pkg::S3 {42, "example_string", {1, 2, 3}, s2_1, {s1_1, s1_2, s1_3}};

        nlohmann::json j = serialize(s3_struct);
        pkg::S3 deserialized_s3 = deserialize<pkg::S3>(j);

        // Проверка значений после десериализации
        assert(deserialized_s3.r1 == 42);
        assert(deserialized_s3.some_str == "example_string");
        assert(deserialized_s3.vals == std::vector<int>({1, 2, 3}));
        assert(deserialized_s3.s2_val.val == 1.23f);
        assert(deserialized_s3.s1_vals.size() == 3);
        assert(deserialized_s3.s1_vals[0].r0 == 1);
        assert(deserialized_s3.s1_vals[1].r0 == 2);
        assert(deserialized_s3.s1_vals[2].r0 == 3);
    }

public:
    static void runTests() {
        testSerializeS1();
        testDeserializeS1();
        testSerializeS2();
        testDeserializeS2();
        testSerializeS3();
        testDeserializeS3();
        std::cout << "All tests passed!" << std::endl;
    }
};

int main(int argc, char *argv[]) {
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

    TestSerializer::runTests();
}