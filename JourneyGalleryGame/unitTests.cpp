#include <gtest/gtest.h>
#include "pugixml.hpp"
#include "Material.h"
#include "Equipment.h"
#include "Inventory.h"


TEST(TestReadXML, TestMaterial) {
    std::string xml = R"(
<?xml version = "1.0"?>
<Material name="testMaterial" sprite="None" nb="2">
    <Shape x="0" y="0"/>
    <Shape x="1" y="0"/>
    <Shape x="0" y="1"/>
</Material>
)";
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(xml.c_str());
    EXPECT_NE(0, result);
    Material mat{doc.child("Material")};
    EXPECT_EQ("testMaterial",mat.get_name());
    EXPECT_EQ("None", mat.get_sprite_path());
    EXPECT_EQ(2, mat.get_nb_copies());

    auto shape = mat.get_shape();
    EXPECT_EQ(0, std::get<0>(shape[0]));
    EXPECT_EQ(0, std::get<1>(shape[0]));
    EXPECT_EQ(1, std::get<0>(shape[1]));
    EXPECT_EQ(0, std::get<1>(shape[1]));
    EXPECT_EQ(0, std::get<0>(shape[2]));
    EXPECT_EQ(1, std::get<1>(shape[2]));
}

TEST(TestReadXML, TestEquipment) {
    std::string xml = R"(
<?xml version = "1.0"?>
<Equipment name="testEquipment" sprite="None" nb="0">
    <Required mat="Material1" need="2"/>
    <Required mat="Material2" need="1"/>
</Equipment>
)";
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(xml.c_str());
    EXPECT_NE(0, result);
    Equipment equip{doc.child("Equipment")};
    EXPECT_EQ("testEquipment", equip.get_name());
    EXPECT_EQ("None", equip.get_sprite_path());
    EXPECT_EQ(0, equip.get_nb_copies());

    auto required = equip.get_required_mats();
    EXPECT_EQ("Material1", std::get<0>(required[0]));
    EXPECT_EQ(2, std::get<1>(required[0]));
    EXPECT_EQ("Material2", std::get<0>(required[1]));
    EXPECT_EQ(1, std::get<1>(required[1]));

}

TEST(TestReadXML, TestInitInventory){
    std::string xml = R"(
<?xml version = "1.0"?>
<Inventory>
    <Material name="Material1" sprite="None" nb="2">
        <Shape x="0" y="0"/>
        <Shape x="1" y="0"/>
        <Shape x="0" y="1"/>
    </Material>
    <Material name="Material2" sprite="None" nb="0">
        <Shape x="0" y="0"/>
        <Shape x="1" y="0"/>
        <Shape x="2" y="0"/>
        <Shape x="3" y="0"/>
        <Shape x="4" y="0"/>
    </Material>
    <Equipment name="testEquipment" sprite="None" nb="0">
        <Required mat="Material1" need="2"/>
        <Required mat="Material2" need="1"/>
    </Equipment>
</Inventory>
)";
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(xml.c_str());
    EXPECT_NE(0, result);
    auto invent = Inventory();
    invent.init_inventory(doc.child("Inventory"));
    auto & mats = invent.get_materials();
    auto & equips = invent.get_equipment();


    EXPECT_EQ("Material1",mats["Material1"]->get_name());
    EXPECT_EQ("None", mats["Material1"]->get_sprite_path());
    EXPECT_EQ(2, mats["Material1"]->get_nb_copies());

    auto shape1 = mats["Material1"]->get_shape();
    EXPECT_EQ(0, std::get<0>(shape1[0]));
    EXPECT_EQ(0, std::get<1>(shape1[0]));
    EXPECT_EQ(1, std::get<0>(shape1[1]));
    EXPECT_EQ(0, std::get<1>(shape1[1]));
    EXPECT_EQ(0, std::get<0>(shape1[2]));
    EXPECT_EQ(1, std::get<1>(shape1[2]));


    EXPECT_EQ("Material2",mats["Material2"]->get_name());
    EXPECT_EQ("None", mats["Material2"]->get_sprite_path());
    EXPECT_EQ(0, mats["Material2"]->get_nb_copies());

    auto shape2 = mats["Material2"]->get_shape();
    EXPECT_EQ(0, std::get<0>(shape2[0]));
    EXPECT_EQ(0, std::get<1>(shape2[0]));
    EXPECT_EQ(1, std::get<0>(shape2[1]));
    EXPECT_EQ(0, std::get<1>(shape2[1]));
    EXPECT_EQ(2, std::get<0>(shape2[2]));
    EXPECT_EQ(0, std::get<1>(shape2[2]));
    EXPECT_EQ(3, std::get<0>(shape2[3]));
    EXPECT_EQ(0, std::get<1>(shape2[3]));
    EXPECT_EQ(4, std::get<0>(shape2[4]));
    EXPECT_EQ(0, std::get<1>(shape2[4]));

    EXPECT_EQ("testEquipment",equips["testEquipment"]->get_name());
    EXPECT_EQ("None", equips["testEquipment"]->get_sprite_path());
    EXPECT_EQ(0, equips["testEquipment"]->get_nb_copies());

    auto required = equips["testEquipment"]->get_required_mats();
    EXPECT_EQ("Material1", std::get<0>(required[0]));
    EXPECT_EQ(2, std::get<1>(required[0]));
    EXPECT_EQ("Material2", std::get<0>(required[1]));
    EXPECT_EQ(1, std::get<1>(required[1]));
}




