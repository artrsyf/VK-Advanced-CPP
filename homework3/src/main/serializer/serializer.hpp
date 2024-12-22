#include <boost/fusion/adapted/struct/define_struct.hpp>
#include <boost/fusion/include/algorithm.hpp>
#include <boost/fusion/include/define_struct.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/transform.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/vector.hpp>

#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#define FIELD_NAME(field) #field

BOOST_FUSION_DEFINE_STRUCT(
    (pkg),
    S1,
    (int, r0))

BOOST_FUSION_DEFINE_STRUCT(
    (pkg),
    S2,
    (float, val))

BOOST_FUSION_DEFINE_STRUCT(
    (pkg),
    S3,
    (int, r1)(std::string, some_str)(std::vector<int>, vals)(pkg::S2, s2_val)(std::vector<pkg::S1>, s1_vals))

template<typename T>
nlohmann::json serialize(const T& obj)
{
    nlohmann::json j;

    boost::fusion::for_each(boost::mpl::range_c<unsigned, 0, boost::fusion::result_of::size<T>::value>(), [&](auto index) {
        auto field = boost::fusion::at_c<index>(obj);
        using FieldType = std::decay_t<decltype(field)>;
        std::string fieldName = boost::fusion::extension::struct_member_name<T, index>::call();

        if constexpr (std::is_same_v<FieldType, std::vector<int>>) {
            j[fieldName] = field;
        } else if constexpr (std::is_same_v<FieldType, std::vector<pkg::S1>>) {
            nlohmann::json arr = nlohmann::json::array();
            for (const auto& item : field) {
                arr.push_back({ { "r0", item.r0 } });
            }
            j[fieldName] = arr;
        } else if constexpr (std::is_same_v<FieldType, pkg::S2>) {
            j[fieldName] = { { "val", field.val } };
        } else if constexpr (std::is_same_v<FieldType, std::string>) {
            j[fieldName] = field;
        } else if constexpr (std::is_same_v<FieldType, int>) {
            j[fieldName] = field;
        } else if constexpr (std::is_same_v<FieldType, float>) {
            j[fieldName] = field;
        } else {
            j[fieldName] = field;
        }
    });

    return j;
}

template<typename T>
T deserialize(const nlohmann::json& j)
{
    T obj;

    boost::fusion::for_each(boost::mpl::range_c<unsigned, 0, boost::fusion::result_of::size<T>::value>(), [&](auto index) {
        auto& field = boost::fusion::at_c<index>(obj);
        using FieldType = std::decay_t<decltype(field)>;
        std::string fieldName = boost::fusion::extension::struct_member_name<T, index>::call();

        if constexpr (std::is_same_v<FieldType, std::vector<int>>) {
            field = j[fieldName].get<std::vector<int>>();
        } else if constexpr (std::is_same_v<FieldType, std::vector<pkg::S1>>) {
            for (const auto& item : j[fieldName]) {
                pkg::S1 s1_item;
                s1_item.r0 = item["r0"].get<int>();
                field.push_back(s1_item);
            }
        } else if constexpr (std::is_same_v<FieldType, pkg::S2>) {
            field.val = j[fieldName]["val"].get<float>();
        } else if constexpr (std::is_same_v<FieldType, std::string>) {
            field = j[fieldName].get<std::string>();
        } else if constexpr (std::is_same_v<FieldType, int>) {
            field = j[fieldName].get<int>();
        } else if constexpr (std::is_same_v<FieldType, float>) {
            field = j[fieldName].get<float>();
        } else {
            field = j[fieldName].get<decltype(field)>();
        }
    });

    return obj;
}