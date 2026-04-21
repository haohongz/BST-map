#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"
#include <sstream>
#include <string>

using namespace std;

// ==================== empty ====================
TEST(test_empty_true) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty());
    ASSERT_EQUAL(tree.size(), 0u);
    ASSERT_EQUAL(tree.height(), 0u);
}

TEST(test_empty_false) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    ASSERT_FALSE(tree.empty());
    ASSERT_EQUAL(tree.size(), 1u);
}

// ==================== size ====================
TEST(test_size_many) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);
    ASSERT_EQUAL(tree.size(), 7u);
}

// ==================== height ====================
TEST(test_height_one) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    ASSERT_EQUAL(tree.height(), 1u);
}

TEST(test_height_balanced) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    ASSERT_EQUAL(tree.height(), 2u);
}

TEST(test_height_left_stick) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(4);
    tree.insert(3);
    tree.insert(2);
    ASSERT_EQUAL(tree.height(), 4u);
}

TEST(test_height_right_stick) {
    BinarySearchTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    ASSERT_EQUAL(tree.height(), 4u);
}

// ==================== traverse_inorder ====================
TEST(test_inorder_empty) {
    BinarySearchTree<int> tree;
    ostringstream oss;
    tree.traverse_inorder(oss);
    ASSERT_EQUAL(oss.str(), "");
}

TEST(test_inorder_many) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);
    ostringstream oss;
    tree.traverse_inorder(oss);
    ASSERT_EQUAL(oss.str(), "1 2 3 4 5 6 7 ");
}

// ==================== traverse_preorder ====================
TEST(test_preorder_empty) {
    BinarySearchTree<int> tree;
    ostringstream oss;
    tree.traverse_preorder(oss);
    ASSERT_EQUAL(oss.str(), "");
}

TEST(test_preorder_three) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    ostringstream oss;
    tree.traverse_preorder(oss);
    ASSERT_EQUAL(oss.str(), "5 3 7 ");
}

TEST(test_preorder_vs_inorder) {
    BinarySearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    ostringstream pre_oss, in_oss;
    tree.traverse_preorder(pre_oss);
    tree.traverse_inorder(in_oss);
    ASSERT_EQUAL(pre_oss.str(), "10 5 15 ");
    ASSERT_EQUAL(in_oss.str(), "5 10 15 ");
}

// ==================== find ====================
TEST(test_find_empty) {
    BinarySearchTree<int> tree;
    ASSERT_EQUAL(tree.find(5), tree.end());
}

TEST(test_find_root) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    ASSERT_NOT_EQUAL(tree.find(5), tree.end());
    ASSERT_EQUAL(*tree.find(5), 5);
}

TEST(test_find_left_right) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    ASSERT_EQUAL(*tree.find(3), 3);
    ASSERT_EQUAL(*tree.find(7), 7);
}

TEST(test_find_not_found) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    ASSERT_EQUAL(tree.find(4), tree.end());
}

TEST(test_find_deep) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    ASSERT_EQUAL(*tree.find(1), 1);
}

// ==================== insert ====================
TEST(test_insert_into_empty) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    ASSERT_FALSE(tree.empty());
    ASSERT_EQUAL(tree.size(), 1u);
    ASSERT_EQUAL(*tree.begin(), 5);
}

TEST(test_insert_left_then_right) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    ostringstream oss;
    tree.traverse_inorder(oss);
    ASSERT_EQUAL(oss.str(), "3 5 7 ");
}

TEST(test_insert_sorted_ascending) {
    BinarySearchTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    ASSERT_EQUAL(tree.size(), 3u);
    ASSERT_EQUAL(tree.height(), 3u);
}

// ==================== min_element / max_element ====================
TEST(test_min_element) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);
    ASSERT_EQUAL(*tree.min_element(), 1);
}

TEST(test_max_element) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);
    ASSERT_EQUAL(*tree.max_element(), 6);
}

TEST(test_min_max_single) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    ASSERT_EQUAL(*tree.min_element(), 5);
    ASSERT_EQUAL(*tree.max_element(), 5);
}

TEST(test_min_max_varied_shapes) {
    // Case 1: Left stick — min is at the bottom (deep recursion)
    BinarySearchTree<int> left_stick;
    left_stick.insert(10);
    left_stick.insert(5);
    left_stick.insert(1);
    ASSERT_EQUAL(*left_stick.min_element(), 1);
    ASSERT_EQUAL(*left_stick.max_element(), 10);

    // Case 2: Right stick — min is root, max is at the bottom
    BinarySearchTree<int> right_stick;
    right_stick.insert(1);
    right_stick.insert(5);
    right_stick.insert(10);
    ASSERT_EQUAL(*right_stick.min_element(), 1);
    ASSERT_EQUAL(*right_stick.max_element(), 10);

    // Case 3: Leftmost node has a RIGHT child — must stop at leftmost
    BinarySearchTree<int> tree1;
    tree1.insert(10);
    tree1.insert(5);
    tree1.insert(7);  // right child of leftmost (5)
    ASSERT_EQUAL(*tree1.min_element(), 5);

    // Case 4: Rightmost node has a LEFT child — must stop at rightmost
    BinarySearchTree<int> tree2;
    tree2.insert(5);
    tree2.insert(10);
    tree2.insert(8);  // left child of rightmost (10)
    ASSERT_EQUAL(*tree2.max_element(), 10);
}

// ==================== min_greater_than ====================
TEST(test_min_greater_than_empty) {
    BinarySearchTree<int> tree;
    ASSERT_EQUAL(tree.min_greater_than(5), tree.end());
}

TEST(test_min_element_empty) {
    BinarySearchTree<int> tree;
    ASSERT_EQUAL(tree.min_element(), tree.end());
}

TEST(test_min_greater_than_found) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);
    ASSERT_EQUAL(*tree.min_greater_than(4), 5);
    ASSERT_EQUAL(*tree.min_greater_than(1), 2);
    ASSERT_EQUAL(*tree.min_greater_than(5), 6);
}

TEST(test_min_greater_than_not_in_tree) {
    BinarySearchTree<int> tree;
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    ASSERT_EQUAL(*tree.min_greater_than(3), 4);
}

TEST(test_min_greater_than_no_result) {
    BinarySearchTree<int> tree;
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    ASSERT_EQUAL(tree.min_greater_than(6), tree.end());
    ASSERT_EQUAL(tree.min_greater_than(100), tree.end());
}

// ==================== check_sorting_invariant ====================
TEST(test_sorting_invariant_empty) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.check_sorting_invariant());
}

TEST(test_sorting_invariant_valid) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    ASSERT_TRUE(tree.check_sorting_invariant());
}

TEST(test_sorting_invariant_broken_root) {
    BinarySearchTree<int> tree;
    tree.insert(1);
    tree.insert(0);
    *tree.begin() = 2;
    ASSERT_FALSE(tree.check_sorting_invariant());
}

TEST(test_sorting_invariant_broken_deep) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);
    *tree.begin() = 5;
    ASSERT_FALSE(tree.check_sorting_invariant());
}

TEST(test_sorting_invariant_broken_right) {
    BinarySearchTree<int> tree;
    tree.insert(3);
    tree.insert(5);
    auto it = tree.begin();
    ++it;
    *it = 1;
    ASSERT_FALSE(tree.check_sorting_invariant());
}

TEST(test_sorting_invariant_equal) {
    BinarySearchTree<int> tree;
    tree.insert(3);
    tree.insert(1);
    tree.insert(5);
    *tree.begin() = 3;
    ASSERT_FALSE(tree.check_sorting_invariant());
}

// ==================== copy constructor (thorough) ====================
TEST(test_copy_basic) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    BinarySearchTree<int> tree2(tree);
    ASSERT_EQUAL(tree2.size(), 3u);
    ASSERT_EQUAL(*tree2.find(4), 4);
    ASSERT_EQUAL(*tree2.find(2), 2);
    ASSERT_EQUAL(*tree2.find(6), 6);
}

TEST(test_copy_empty) {
    BinarySearchTree<int> tree;
    BinarySearchTree<int> tree2(tree);
    ASSERT_TRUE(tree2.empty());
}

TEST(test_copy_preserves_structure) {
    // Verify EXACT structure is preserved (not just elements)
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);
    BinarySearchTree<int> tree2(tree);
    ASSERT_EQUAL(tree2.size(), tree.size());
    ASSERT_EQUAL(tree2.height(), tree.height());
    ostringstream oss1, oss2;
    tree.traverse_preorder(oss1);
    tree2.traverse_preorder(oss2);
    ASSERT_EQUAL(oss1.str(), oss2.str());
}

TEST(test_copy_is_deep) {
    // Modify original after copy → copy must be unaffected
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    BinarySearchTree<int> tree2(tree);
    *tree.begin() = 99;
    ASSERT_EQUAL(*tree2.begin(), 3);
    ASSERT_EQUAL(tree2.size(), 3u);
    ASSERT_TRUE(tree2.check_sorting_invariant());
}

TEST(test_copy_single_node) {
    BinarySearchTree<int> tree;
    tree.insert(42);
    BinarySearchTree<int> tree2(tree);
    ASSERT_EQUAL(tree2.size(), 1u);
    ASSERT_EQUAL(*tree2.begin(), 42);
    ASSERT_EQUAL(tree2.height(), 1u);
}

TEST(test_copy_left_stick) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(4);
    tree.insert(3);
    BinarySearchTree<int> tree2(tree);
    ASSERT_EQUAL(tree2.size(), 3u);
    ASSERT_EQUAL(tree2.height(), 3u);
    ASSERT_EQUAL(*tree2.min_element(), 3);
    ASSERT_EQUAL(*tree2.max_element(), 5);
    ostringstream oss1, oss2;
    tree.traverse_inorder(oss1);
    tree2.traverse_inorder(oss2);
    ASSERT_EQUAL(oss1.str(), oss2.str());
}

TEST(test_copy_right_stick) {
    BinarySearchTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    BinarySearchTree<int> tree2(tree);
    ASSERT_EQUAL(tree2.size(), 3u);
    ASSERT_EQUAL(tree2.height(), 3u);
    ASSERT_EQUAL(*tree2.min_element(), 1);
    ASSERT_EQUAL(*tree2.max_element(), 3);
    ostringstream oss1, oss2;
    tree.traverse_inorder(oss1);
    tree2.traverse_inorder(oss2);
    ASSERT_EQUAL(oss1.str(), oss2.str());
}

// ==================== assignment operator ====================
TEST(test_assignment) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    BinarySearchTree<int> tree2;
    tree2 = tree;
    ASSERT_EQUAL(tree2.size(), 3u);
    ASSERT_EQUAL(*tree2.find(4), 4);
}

// ==================== iterator ====================
TEST(test_iterator_begin_end) {
    BinarySearchTree<int> tree;
    ASSERT_EQUAL(tree.begin(), tree.end());
}

TEST(test_iterator_full_traversal) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);
    ostringstream oss;
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        oss << *it << " ";
    }
    ASSERT_EQUAL(oss.str(), "1 2 3 4 5 6 7 ");
}

TEST(test_iterator_postfix) {
    BinarySearchTree<int> tree;
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);
    auto it = tree.begin();
    ASSERT_EQUAL(*it++, 1);
    ASSERT_EQUAL(*it, 2);
}

// ==================== custom comparator ====================
TEST(test_custom_comparator) {
    BinarySearchTree<int, std::greater<int>> tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    ASSERT_EQUAL(*tree.min_element(), 6);
    ASSERT_EQUAL(*tree.max_element(), 2);
}

// ==================== string type ====================
TEST(test_string_bst) {
    BinarySearchTree<string> tree;
    tree.insert("dog");
    tree.insert("cat");
    tree.insert("fish");
    ASSERT_EQUAL(*tree.min_element(), "cat");
    ASSERT_EQUAL(*tree.max_element(), "fish");
    ASSERT_EQUAL(tree.size(), 3u);
}

// ==================== ostream ====================
TEST(test_ostream) {
    BinarySearchTree<int> tree;
    ostringstream oss1;
    oss1 << tree;
    ASSERT_EQUAL(oss1.str(), "[ ]");
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    ostringstream oss2;
    oss2 << tree;
    ASSERT_EQUAL(oss2.str(), "[ 2 4 6 ]");
}



TEST_MAIN()