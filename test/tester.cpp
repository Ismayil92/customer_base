#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <kunde.hpp>


class KundeArhiveTest: public testing::Test{
public:
    KundeArchive database{"../../test/test_base.csv"};
    std::map<int, CUSTOMER> container;
    
    void SetUp() override{
        container = database.getData();              
    }
    void TearDown() override{}
};

TEST_F(KundeArhiveTest,GENERATEID){
    //current id = 5;
    int next_id = database.generateID(container);
    EXPECT_EQ(next_id,6);
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
