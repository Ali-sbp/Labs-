#include <cassert>
#include <iostream>
#include <fstream>
#include <cmath>
#include "../src/list.hpp"


void testEmptyList() {
    std::cout << "Testing empty list..." << std::endl;
    
    List list;
    assert(list.isEmpty());
    assert(list.size() == 0);
    assert(list.getCircleAt(0) == nullptr);
    assert(list.find(Circle(0,0,1)) == nullptr);
    assert(list.removeFirst(Circle(0,0,1)) == false);
    assert(list.removeAll(Circle(0,0,1)) == 0);
    
    std::cout << "Empty list tests: PASSED" << std::endl;
}

void testAddingElements() {
    std::cout << "Testing adding elements..." << std::endl;
    
    List list;
    Circle c1(1.0, 2.0, 3.0);
    Circle c2(4.0, 5.0, 6.0);
    Circle c3(7.0, 8.0, 9.0);
    
    // Test addToFront
    list.addToFront(c1);
    assert(!list.isEmpty());
    assert(list.size() == 1);
    
    Circle* first = list.getCircleAt(0);
    assert(first != nullptr);
    assert(*first == c1);
    delete first;
    
    // Test addToEnd
    list.addToEnd(c2);
    assert(list.size() == 2);
    
    Circle* second = list.getCircleAt(1);
    assert(second != nullptr);
    assert(*second == c2);
    delete second;
    
    // Add one more to front to test ordering
    list.addToFront(c3);
    assert(list.size() == 3);
    
    first = list.getCircleAt(0);
    assert(*first == c3);
    delete first;
    
    Circle* middle = list.getCircleAt(1);
    assert(*middle == c1);
    delete middle;
    
    std::cout << "Adding elements tests: PASSED" << std::endl;
}

void testFindingElements() {
    std::cout << "Testing finding elements..." << std::endl;
    
    List list;
    Circle c1(1.0, 2.0, 3.0);
    Circle c2(4.0, 5.0, 6.0);
    Circle c3(7.0, 8.0, 9.0);
    
    list.addToFront(c1);
    list.addToEnd(c2);
    list.addToFront(c3);
    
    // Find existing elements
    Node* foundNode = list.find(c1);
    assert(foundNode != nullptr);
    assert(foundNode->getData() == c1);
    
    foundNode = list.find(c2);
    assert(foundNode != nullptr);
    assert(foundNode->getData() == c2);
    
    foundNode = list.find(c3);
    assert(foundNode != nullptr);
    assert(foundNode->getData() == c3);
    
    // Find non-existing element
    Circle nonExistent(99.0, 99.0, 99.0);
    foundNode = list.find(nonExistent);
    assert(foundNode == nullptr);
    
    std::cout << "Finding elements tests: PASSED" << std::endl;
}

void testRemovingElements() {
    std::cout << "Testing removing elements..." << std::endl;
    
    List list;
    Circle c1(1.0, 2.0, 3.0);
    Circle c2(4.0, 5.0, 6.0);
    Circle c3(1.0, 2.0, 3.0); // Same as c1
    Circle c4(7.0, 8.0, 9.0);
    
    list.addToFront(c1);
    list.addToEnd(c2);
    list.addToFront(c3);  // List: c3(same as c1), c1, c2
    assert(list.size() == 3);
    
    // Test removeFirst
    bool removed = list.removeFirst(c1);
    assert(removed);
    assert(list.size() == 2);
    
    // Check that only the first occurrence was removed
    Circle* remaining = list.getCircleAt(0);
    assert(remaining != nullptr);
    assert(*remaining == c1); // c3 is same as c1, and should still be there
    delete remaining;
    
    // Remove another
    removed = list.removeFirst(c1);
    assert(removed);
    assert(list.size() == 1);
    
    // Try removing non-existent
    removed = list.removeFirst(c1);
    assert(!removed);
    assert(list.size() == 1);
    
    // Test removeAll with multiple identical elements
    list.clear();
    list.addToFront(c1);
    list.addToFront(c1);
    list.addToEnd(c2);
    list.addToFront(c1);
    list.addToEnd(c4);
    list.addToFront(c1);
    assert(list.size() == 6);
    
    size_t countRemoved = list.removeAll(c1);
    assert(countRemoved == 4);
    assert(list.size() == 2);
    
    // Verify remaining elements are c2 and c4
    Circle* first = list.getCircleAt(0);
    Circle* second = list.getCircleAt(1);
    
    assert((*first == c2 && *second == c4) || (*first == c4 && *second == c2));
    
    delete first;
    delete second;
    
    std::cout << "Removing elements tests: PASSED" << std::endl;
}

void testClearAndSize() {
    std::cout << "Testing clear and size..." << std::endl;
    
    List list;
    
    // Empty list
    assert(list.isEmpty());
    assert(list.size() == 0);
    
    // Add elements
    Circle c1(1.0, 2.0, 3.0);
    list.addToFront(c1);
    list.addToFront(c1);
    list.addToFront(c1);
    
    assert(!list.isEmpty());
    assert(list.size() == 3);
    
    // Clear
    list.clear();
    assert(list.isEmpty());
    assert(list.size() == 0);
    
    // Add more elements after clearing
    list.addToFront(c1);
    assert(!list.isEmpty());
    assert(list.size() == 1);
    
    std::cout << "Clear and size tests: PASSED" << std::endl;
}

void testSorting() {
    std::cout << "Testing sorting..." << std::endl;
    
    List list;
    
    // Test empty list sort (shouldn't crash)
    list.sort();
    
    // Test single element sort
    Circle c1(0.0, 0.0, 5.0); // Area = 25π
    list.addToFront(c1);
    list.sort();
    assert(list.size() == 1);
    
    // Test multiple element sort
    list.clear();
    Circle c2(0.0, 0.0, 3.0); // Area = 9π
    Circle c3(0.0, 0.0, 1.0); // Area = π
    Circle c4(0.0, 0.0, 4.0); // Area = 16π
    Circle c5(0.0, 0.0, 2.0); // Area = 4π
    
    list.addToFront(c2); // 9π
    list.addToFront(c3); // π
    list.addToFront(c4); // 16π
    list.addToFront(c5); // 4π
    
    list.sort();
    
    // Check if sorted by area (ascending)
    Circle* first = list.getCircleAt(0);
    Circle* second = list.getCircleAt(1);
    Circle* third = list.getCircleAt(2);
    Circle* fourth = list.getCircleAt(3);
    
    assert(first->getRadius() == 1.0);  // π
    assert(second->getRadius() == 2.0); // 4π
    assert(third->getRadius() == 3.0);  // 9π
    assert(fourth->getRadius() == 4.0); // 16π
    
    delete first;
    delete second;
    delete third;
    delete fourth;
    
    std::cout << "Sorting tests: PASSED" << std::endl;
}

void testFileIO() {
    std::cout << "Testing file I/O..." << std::endl;
    
    // Test saving and loading empty list
    {
        List emptyList;
        emptyList.saveToFile("empty_test.txt");
        
        List loadedEmpty;
        loadedEmpty.loadFromFile("empty_test.txt");
        
        assert(loadedEmpty.isEmpty());
        assert(loadedEmpty.size() == 0);
    }
    
    // Test saving and loading with elements
    {
        List list;
        Circle c1(1.0, 2.0, 3.0);
        Circle c2(4.0, 5.0, 6.0);
        Circle c3(7.0, 8.0, 9.0);
        
        list.addToFront(c3);
        list.addToFront(c1);
        list.addToEnd(c2);
        
        list.saveToFile("test_circles.txt");
        
        List loadedList;
        loadedList.loadFromFile("test_circles.txt");
        
        assert(loadedList.size() == 3);
        
        Circle* first = loadedList.getCircleAt(0);
        Circle* second = loadedList.getCircleAt(1);
        Circle* third = loadedList.getCircleAt(2);
        
        assert(first != nullptr);
        assert(second != nullptr);
        assert(third != nullptr);
        
        // The circles might not be in the same order depending on how saveToFile
        // traverses the list, so we just check that all three circles are present
        bool c1Found = false, c2Found = false, c3Found = false;
        
        if (*first == c1 || *second == c1 || *third == c1) c1Found = true;
        if (*first == c2 || *second == c2 || *third == c2) c2Found = true;
        if (*first == c3 || *second == c3 || *third == c3) c3Found = true;
        
        assert(c1Found && c2Found && c3Found);
        
        delete first;
        delete second;
        delete third;
    }
    
    // Test error handling - missing file
    {
        List list;
        list.loadFromFile("nonexistent_file.txt");
        assert(list.isEmpty());
    }
    
    std::cout << "File I/O tests: PASSED" << std::endl;
}

void testOptionalMethods() {
    std::cout << "Testing optional methods..." << std::endl;
    
    List list;
    Circle c1(0.0, 0.0, 1.0);
    Circle c2(0.0, 0.0, 2.0);
    Circle c3(0.0, 0.0, 3.0);
    Circle c4(0.0, 0.0, 4.0);
    
    list.addToEnd(c1);
    list.addToEnd(c2);
    list.addToEnd(c3);
    list.addToEnd(c4);
    
    // Test countCirclesWithRadiusGreaterThan
    size_t count = list.countCirclesWithRadiusGreaterThan(2.5);
    assert(count == 2); // c3 and c4 have radius > 2.5
    
    count = list.countCirclesWithRadiusGreaterThan(0.5);
    assert(count == 4); // all circles have radius > 0.5
    
    count = list.countCirclesWithRadiusGreaterThan(5.0);
    assert(count == 0); // no circles have radius > 5.0
    
    std::cout << "Optional methods tests: PASSED" << std::endl;
}

int main() {
    std::cout << "========== List Class Tests ==========" << std::endl;
    
    testEmptyList();
    testAddingElements();
    testFindingElements();
    testRemovingElements();
    testClearAndSize();
    testSorting();
    testFileIO();
    testOptionalMethods();
    
    std::cout << "All List class tests PASSED!" << std::endl;
    return 0;
}