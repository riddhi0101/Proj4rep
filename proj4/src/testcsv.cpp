#include <gtest/gtest.h>
#include "CSVReader.h"
#include "XMLReader.h"
#include "XMLEntity.h"
#include "CSVWriter.h"
#include "XMLWriter.h"
#include<>
TEST(Convertertest, READ_CSV){
    CCSVReader test1("""hello","bye""");
    std::vector <std::string> rowe;
    test1.ReadRow(rowe);
    EXPECT_EQ(rowe,<""hello","bye"">);

    CCSVReader test2(" 1,2 , 	3	  ,4,5")
    CCSVReader test3("""abc " /n" ,123""")



    std::stringstream Input(" 1,2 ,  3         ,4,5\x0d\x0a");
    CCSVReader Reader(Input);
    std::vector <std::string> Row;

    EXPECT_TRUE(Reader.ReadRow(Row));
    EXPECT_EQ(Row.size(),5);
    if (Row.size() >= 5){
        EXPECT_EQ(Row[0], "1");
        EXPECT_EQ(Row[0], "2");
        EXPECT_EQ(Row[0], "3");
        EXPECT_EQ(Row[0], "4");
        EXPECT_EQ(Row[0], "5");
    }
    EXPECT_FALSE(Reader.ReadRow(Row));

}

TEST(CSVWriter, BasicTest){
    std::stringstream Output;
    CCSVWriter Writer(Output);
    std::vector< std::string > Row{"1","2","3","4","5"};

    EXPECT_TRUE(Writer.WriteRow(Row));
    EXPECT_EQ(Output.str(),"\"1\",\"2,\"3\",\"4\",\"5\"");
}

TEST(Convertertest, XML_TO_CSV){
// Needs to test that setting up an initial board is correct
}

TEST(Convertertest, EMPTY_CSV){
// Needs to test that resetting a board is correct
}