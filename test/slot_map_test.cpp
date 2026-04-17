#include <gtest/gtest.h>
#include <slotmap/slotmap.h>

TEST(SlotMapTest, EmptySlotMapTest)
{
    slot_map<std::string> sm {};
    EXPECT_EQ(sm.size(), 0);
    EXPECT_EQ(sm.data_indices().size(), 0);
    EXPECT_EQ(sm.data_keys().size(), 0);
}

TEST(SlotMapTest, PushBack)
{
    slot_map<std::string> sm {};
    sm.push_back("A");
    EXPECT_EQ(sm.size(), 1);
    EXPECT_EQ(sm.data_indices().size(), 1);
    EXPECT_EQ(sm.data_keys().size(), 1);
    EXPECT_EQ(sm[0], "A");
    
    sm.push_back("B");
    EXPECT_EQ(sm.size(), 2);
    EXPECT_EQ(sm.data_indices().size(), 2);
    EXPECT_EQ(sm.data_keys().size(), 2);
    EXPECT_EQ(sm[1], "B");
}

TEST(SlotMapTest, EmplaceBack)
{
    slot_map<std::string> sm {};
    sm.emplace_back("A");
    EXPECT_EQ(sm.size(), 1);
    EXPECT_EQ(sm.data_indices().size(), 1);
    EXPECT_EQ(sm.data_keys().size(), 1);
    EXPECT_EQ(sm[0], "A");
    
    sm.emplace_back("B");
    EXPECT_EQ(sm.size(), 2);
    EXPECT_EQ(sm.data_indices().size(), 2);
    EXPECT_EQ(sm.data_keys().size(), 2);
    EXPECT_EQ(sm[1], "B");
}

TEST(SlotMapTest, Iteration)
{
    slot_map<std::string> sm {};
    const auto & const_ref = sm;
    sm.push_back("A");

    std::size_t count = 0;
    for ( auto & elem : sm )
    {
        ++count;
        EXPECT_EQ(elem, "A");
    }
    EXPECT_EQ(count, 1);
    
    count = 0;
    for ( const auto & elem : sm )
    {
        ++count;
        EXPECT_EQ(elem, "A");
    }
    EXPECT_EQ(count, 1);

    count = 0;
    for ( auto & elem : const_ref )
    {
        ++count;
        EXPECT_EQ(elem, "A");
    }
    EXPECT_EQ(count, 1);
    
    count = 0;
    for ( const auto & elem : const_ref )
    {
        ++count;
        EXPECT_EQ(elem, "A");
    }
    EXPECT_EQ(count, 1);

    count = 0;
    for ( auto it = sm.begin(); it != sm.end(); ++it )
    {
        ++count;
        EXPECT_EQ(*it, "A");
    }
    EXPECT_EQ(count, 1);

    count = 0;
    for ( auto it = const_ref.begin(); it != const_ref.end(); ++it )
    {
        ++count;
        EXPECT_EQ(*it, "A");
    }
    EXPECT_EQ(count, 1);

    sm.push_back("B");
    const std::string expected[] {"A", "B"};
    count = 0;
    for ( auto & elem : sm )
    {
        EXPECT_EQ(elem, expected[count]);
        ++count;
    }
    EXPECT_EQ(count, 2);
}

TEST(SlotMapTest, ArrayOp)
{
    slot_map<std::string> sm {};
    sm.push_back("A");
    sm.push_back("B");
    EXPECT_EQ(sm[0], "A");
    EXPECT_EQ(sm[1], "B");

    const auto & const_ref = sm;
    EXPECT_EQ(const_ref[0], "A");
    EXPECT_EQ(const_ref[1], "B");

}

TEST(SlotMapTest, CtorVector)
{
    slot_map<std::string> sm({"A", "B", "C"});
    EXPECT_EQ(3, sm.size());
    EXPECT_EQ("A", sm[0]);
    EXPECT_EQ("B", sm[1]);
    EXPECT_EQ("C", sm[2]);

    std::vector<std::string> explicitly_moved {"A", "B", "C"};
    slot_map<std::string> sm2(std::move(explicitly_moved));
    EXPECT_EQ(3, sm2.size());
    EXPECT_EQ("A", sm2[0]);
    EXPECT_EQ("B", sm2[1]);
    EXPECT_EQ("C", sm2[2]);

    std::vector<std::string> copied {"A", "B", "C"};
    slot_map<std::string> sm3(copied);
    EXPECT_EQ(3, sm3.size());
    EXPECT_EQ("A", sm3[0]);
    EXPECT_EQ("B", sm3[1]);
    EXPECT_EQ("C", sm3[2]);
}

TEST(SlotMapTest, AssignVector)
{
    slot_map<std::string> sm {};
    sm = {"A", "B", "C"};
    EXPECT_EQ(3, sm.size());
    EXPECT_EQ("A", sm[0]);
    EXPECT_EQ("B", sm[1]);
    EXPECT_EQ("C", sm[2]);

    std::vector<std::string> explicitly_moved {"A", "B", "C"};
    sm = std::move(explicitly_moved);
    EXPECT_EQ(3, sm.size());
    EXPECT_EQ("A", sm[0]);
    EXPECT_EQ("B", sm[1]);
    EXPECT_EQ("C", sm[2]);

    std::vector<std::string> copied {"A", "B", "C"};
    sm = copied;
    EXPECT_EQ(3, sm.size());
    EXPECT_EQ("A", sm[0]);
    EXPECT_EQ("B", sm[1]);
    EXPECT_EQ("C", sm[2]);
}

TEST(SlotMapTest, CopyCtorAssignmentOp)
{
    slot_map<std::string> sm({"A", "B", "C"});
    slot_map<std::string> sm_copy_ctor(sm);
    EXPECT_EQ(3, sm_copy_ctor.size());
    EXPECT_EQ("A", sm_copy_ctor[0]);
    EXPECT_EQ("B", sm_copy_ctor[1]);
    EXPECT_EQ("C", sm_copy_ctor[2]);
    
    slot_map<std::string> sm_assign_copy {};
    sm_assign_copy = sm;
    EXPECT_EQ(3, sm_assign_copy.size());
    EXPECT_EQ("A", sm_assign_copy[0]);
    EXPECT_EQ("B", sm_assign_copy[1]);
    EXPECT_EQ("C", sm_assign_copy[2]);
}

TEST(SlotMapTest, MoveCtorMoveAssignmentOp)
{
    slot_map<std::string> sm({"A", "B", "C"});
    slot_map<std::string> sm_copy_ctor(std::move(sm));
    EXPECT_EQ(3, sm_copy_ctor.size());
    EXPECT_EQ("A", sm_copy_ctor[0]);
    EXPECT_EQ("B", sm_copy_ctor[1]);
    EXPECT_EQ("C", sm_copy_ctor[2]);
    
    slot_map<std::string> sm_assign_copy {};
    sm_assign_copy = std::move(sm_copy_ctor);
    EXPECT_EQ(3, sm_assign_copy.size());
    EXPECT_EQ("A", sm_assign_copy[0]);
    EXPECT_EQ("B", sm_assign_copy[1]);
    EXPECT_EQ("C", sm_assign_copy[2]);
}

TEST(SlotMapTest, Size)
{
    slot_map<std::string> sm {};
    EXPECT_EQ(0, sm.size());
    sm.push_back("A");
    EXPECT_EQ(1, sm.size());
    sm.push_back("B");
    EXPECT_EQ(2, sm.size());
}

auto expect_contents_eq = [](const slot_map<std::string> & sm,
    const std::vector<std::string> & data,
    const std::vector<std::uint64_t> & indicies,
    const std::vector<std::uint64_t> & keys)
{
    EXPECT_EQ(sm.unordered_data(), data);
    EXPECT_EQ(sm.data_indices(), indicies);
    EXPECT_EQ(sm.data_keys(), keys);
};

TEST(SlotMapTest, Erase)
{
    {
        slot_map<std::string> sm {};
        EXPECT_ANY_THROW(sm.erase(0));
    }{
        slot_map<std::string> sm({"A"});
        EXPECT_ANY_THROW(sm.erase(1));
    }{
        slot_map<std::string> sm({"A"});
        expect_contents_eq(sm, {"A"}, {0}, {0});
        sm.erase(0);
        expect_contents_eq(sm, {}, {0}, {0});
        EXPECT_ANY_THROW(sm.erase(0));
    }{
        slot_map<std::string> sm({"A", "B"});
        expect_contents_eq(sm, {"A", "B"}, {0, 1}, {0, 1});
        sm.erase(0);
        expect_contents_eq(sm, {"B"}, {1, 0}, {1, 0});
        EXPECT_EQ(sm[1], "B");
        sm.erase(1);
        expect_contents_eq(sm, {}, {1, 0}, {1, 0});
    }{
        slot_map<std::string> sm({"A", "B"});
        expect_contents_eq(sm, {"A", "B"}, {0, 1}, {0, 1});
        sm.erase(1);
        expect_contents_eq(sm, {"A"}, {0, 1}, {0, 1});
        EXPECT_EQ(sm[0], "A");
        sm.erase(0);
        expect_contents_eq(sm, {}, {0, 1}, {0, 1});
    }{
        slot_map<std::string> sm({"A", "B", "C"});
        expect_contents_eq(sm, {"A", "B", "C"}, {0, 1, 2}, {0, 1, 2});
        sm.erase(1);
        expect_contents_eq(sm, {"A", "C"}, {0, 2, 1}, {0, 2, 1});
        EXPECT_EQ(sm[0], "A");
        EXPECT_EQ(sm[2], "C");
        EXPECT_ANY_THROW(sm.erase(1));
    }
}

TEST(SlotMapTest, PopBack)
{
    {
        slot_map<std::string> sm({"A", "B", "C"});
        expect_contents_eq(sm, {"A", "B", "C"}, {0, 1, 2}, {0, 1, 2});
        sm.pop_back();
        expect_contents_eq(sm, {"A", "B"}, {0, 1, 2}, {0, 1, 2});
        sm.pop_back();
        expect_contents_eq(sm, {"A"}, {0, 1, 2}, {0, 1, 2});
        sm.pop_back();
        expect_contents_eq(sm, {}, {0, 1, 2}, {0, 1, 2});
    }
}

TEST(SlotMapTest, Clear)
{
    slot_map<std::string> sm({"A", "B", "C"});
    expect_contents_eq(sm, {"A", "B", "C"}, {0, 1, 2}, {0, 1, 2});
    sm.clear();
    expect_contents_eq(sm, {}, {}, {});
}

TEST(SlotMapTest, PushPopEraseArrayAccess)
{
    slot_map<std::string> sm {};
    const auto a_key = sm.push_back("A");
    const auto b_key = sm.push_back("B");
    expect_contents_eq(sm, {"A", "B"}, {0, 1}, {0, 1});
    EXPECT_EQ("A", sm[a_key]);
    EXPECT_EQ("B", sm[b_key]);
    sm.erase(0);
    expect_contents_eq(sm, {"B"}, {1, 0}, {1, 0});
    EXPECT_EQ("B", sm[b_key]);
    const auto c_key = sm.push_back("C");
    expect_contents_eq(sm, {"B", "C"}, {1, 0}, {1, 0});
    EXPECT_EQ("B", sm[b_key]);
    EXPECT_EQ("C", sm[c_key]);
    sm.pop_back();
    expect_contents_eq(sm, {"B"}, {1, 0}, {1, 0});
    EXPECT_EQ("B", sm[b_key]);
    sm.pop_back();
    expect_contents_eq(sm, {}, {1, 0}, {1, 0});
}
