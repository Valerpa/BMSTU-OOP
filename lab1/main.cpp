#include <iostream>
#include <iterator.h>
#include <list.h>

using namespace std;

void operator_equal_test();
void add_method_test();
void add_range_method_test();
void add_range_2_method_test();
void set_elem_method_test();
void get_elem_method_test();
void remove_elem_method_test();
void combine_method_test();
void get_index_method_test();
int ascend_compare(const int& r1 , const int& r2);
int descend_compare(const int& r1 , const int& r2);
void sort_method_test();
void operator_array_access_test();
void push_front_method_test();
void pop_front_method_test();
void reverse_method_test();
void insert_after_method_test();

int main() {
    operator_equal_test();
    add_method_test();
    add_range_method_test();
    add_range_2_method_test();
    set_elem_method_test();
    remove_elem_method_test();
    combine_method_test();
    get_index_method_test();
    sort_method_test();
    operator_array_access_test();
    push_front_method_test();
    pop_front_method_test();
    reverse_method_test();
    insert_after_method_test();
}


void operator_equal_test() {
    try {
    cout << "Testing equal operator..." << endl;
    List<int> lst{1,2,3};
    List<int> lst2{3,5,3};
    lst = lst2;
    if (lst == lst2) {
        cout << "PASSED!" << endl << endl;
        }
    }
    catch (List_size_exception& ex){
        cout << ex.what() << endl;
        cout << "PASSED!" << endl << endl;
    }
    cout << "Test finished!" << endl << endl;
}

void add_method_test() {
    cout << "Testing add() method..." << endl;
    try{
    List<int> lst;
    lst.add(1);
    lst.add(2);
    lst.add(3);
    List<int> lst2;
    lst2.add(1);
    lst2.add(2);
    lst2.add(3);
    if (lst == lst2) {
        cout << "PASSED!" << endl << endl;
    }
    else {
        cout << "FAILED!" << endl << endl;
    }
    cout << "1) adding new element..." << endl;
    lst2.add(4);
    if (lst == lst2) {
        cout << "FAILED!" << endl << endl;
    }
    else {
        cout << "PASSED!" << endl << endl;
    }
    } catch (std::bad_alloc& ex) {
        cout << "Error: " << ex.what() << endl;
        cout << "PASSED!" << endl << endl;
    }

    cout << "Test finished!" << endl << endl;
}

void add_range_method_test() {
    cout << "Testing add_range(list) method..." << endl;
    List<int> list1;
    list1.add(1);
    list1.add(2);
    list1.add(3);

    List<int> list2;
    list2.add(4);
    list2.add(5);
    list2.add(6);

    list1.add_range(list2);

    List<int> expected;
    expected.add(1);
    expected.add(2);
    expected.add(3);
    expected.add(4);
    expected.add(5);
    expected.add(6);

    if (list1 == expected) {
        cout << "PASSED!" << endl << endl;
    }
    else {
        cout << "FAILED!" << endl << endl;
    }

    cout << "Test finished!" << endl << endl;
}

void add_range_2_method_test() {
    cout << "Testing add_range(array) method..." << endl;
    int arr1[] = {1, 2, 3};
    List<int> list1;
    list1.add_range(arr1, 3);
    List<int> expected_list;
    expected_list.add(1);
    expected_list.add(2);
    expected_list.add(3);
    if (list1 == expected_list) {
        cout << "PASSED!" << endl << endl;
    }

    try {
        cout << "1) testing array = nullptr..." << endl;
        int *arr3 = nullptr;
        List<int> list3;
        list3.add_range(arr3, 3);
    }  catch (Array_exception& ex1) {
        cout << "Error: " << ex1.what() << endl;
        cout << "PASSED!" << endl << endl;
    }
    try {
        cout << "2) testing array size = 0..." << endl;
        int arr4[] = {1, 2, 3};
        List<int> list4;
        list4.add_range(arr4, 0);
    } catch (Array_exception& ex2) {
        cout << "Error: " <<  ex2.what() << endl;
        cout << "PASSED!" << endl << endl;
    }
    cout << "Test finished!" << endl << endl;

}

void set_elem_method_test() {
    cout << "Testing set_elem() method..." << endl;
    List<int> list1;
    list1.add(1);
    list1.add(2);
    list1.add(3);
    list1.set_elem(1,8);
    List<int> expected_list;
    expected_list.add(1);
    expected_list.add(8);
    expected_list.add(3);
    if (list1 == expected_list) {
        cout << "PASSED!" << endl << endl;
    }
    try {
        cout << "1) testing index < 0..." << endl;
        list1.set_elem(-1, 5);
    } catch (Range_exception &ex1) {
        cout << "Error: " << ex1.what() << endl;
        cout << "PASSED!" << endl << endl;
    }
    try {
        cout << "2) testing index < list size..." << endl;
        list1.set_elem(3, 5);
    } catch (Range_exception& ex2) {
        cout << "Error: " << ex2.what() << endl;
        cout << "PASSED!" << endl << endl;
    }
    cout << "Test finished!" << endl << endl;

}

void get_elem_method_test() {
    cout << "Testing get_elem() method...";
    List<int> list1;
    list1.add(1);
    list1.add(2);
    list1.add(3);
    int& elem = list1.get_elem(1);
    if (elem == 2) {
        cout << "PASSED!" << endl << endl;
    }
    try {
        cout << "1) testing index < 0..." << endl;
        list1.get_elem(-1);
    } catch (Range_exception& ex1) {
        cout << "Error: " << ex1.what() << endl;
        cout << "PASSED!" << endl << endl;
    }

    try {
        cout << "2) testing index > list size..." << endl;
        list1.get_elem(3);
    } catch (Range_exception& ex2) {
        cout << "Error: " << ex2.what() << endl;
        cout << "PASSED!" << endl << endl;
    }
    cout << "Test finished!" << endl << endl;
}

void remove_elem_method_test() {
    cout << "Testing remove_elem() method...";
    List<int> list1;
    list1.add(1);
    list1.add(2);
    list1.add(3);
    list1.remove_elem(1);
    List<int> expected_list;
    expected_list.add(1);
    expected_list.add(3);
    if (list1 == expected_list) {
        cout << "PASSED!" << endl << endl;
    }
    try {
        cout << "1) testing index < 0..." << endl;
        list1.remove_elem(-1);
    } catch (Range_exception& ex1) {
        cout << "Error: " << ex1.what() << endl;
        cout << "PASSED!" << endl << endl;
    }

    try {
        cout << "2) testing index > list size..." << endl;
        list1.remove_elem(3);
    } catch (Range_exception& ex2) {
        cout << "Error: " << ex2.what() << endl;
        cout << "PASSED!" << endl << endl;
    }
    cout << "Test finished!" << endl << endl;
}

void combine_method_test() {
    cout << "Testing combine() method..." << endl;
    List<int> list1;
    list1.add(1);
    list1.add(2);
    list1.add(3);

    List<int> list2;
    list2.add(4);
    list2.add(5);
    list2.add(6);

    List<int> list3;
    list3 = list1.combine(list2);

    List<int> expected;
    expected.add(1);
    expected.add(2);
    expected.add(3);
    expected.add(4);
    expected.add(5);
    expected.add(6);

    if (list3 == expected) {
        cout << "PASSED!" << endl << endl;
    }
    else {
        cout << "FAILED!" << endl << endl;
    }
    cout << "Test finished!" << endl << endl;
}

void get_index_method_test() {
    cout << "Testing get_index() method..." << endl;
    List<int> list1;
    list1.add(1);
    list1.add(2);
    list1.add(3);
    int b = 2;
    int index = list1.get_index(b);
    if (index == 1) {
        cout << "PASSED!" << endl << endl;
    }
    try {
        cout << "1) checking empty list..." << endl;
        List<int> list2;
        int elem = 3;
        int b = list2.get_index(elem);
    } catch (List_size_exception& ex1) {
        cout << "Error: " << ex1.what() << endl;
        cout << "PASSED!" << endl << endl;
    }

    cout << "2) check the index of the element that is not in the list..." << endl;
    int wrong_elem = 5;
    int ind = list1.get_index(wrong_elem);
    if (ind == -1) {
        cout << "There is no such element in list!" << endl;
        cout << "PASSED!" << endl << endl;
    }
    cout << "Test finished!" << endl << endl;

}

int ascend_compare(const int& r1 , const int& r2) {
    return (r1 > r2) ? (1) : (0);
}

int descend_compare(const int& r1 , const int& r2) {
    return (r1 < r2) ? (1) : (0);
}

void sort_method_test() {
    cout << "Testing sort() method operator..." << endl;
    List<int> lst;
    lst.add(1);
    lst.add(4);
    lst.add(-2);
    lst.add(3);
    lst.add(2);
    List<int> expected_list1;
    expected_list1.add(-2);
    expected_list1.add(1);
    expected_list1.add(2);
    expected_list1.add(3);
    expected_list1.add(4);

    List<int> expected_list2;
    expected_list2.add(4);
    expected_list2.add(3);
    expected_list2.add(2);
    expected_list2.add(1);
    expected_list2.add(-2);
    cout << "1) testing ascending sort..." << endl;
    lst.sort(ascend_compare); //void sort(int (*comp)(const T& r1, const T& r2))
    if (lst == expected_list1) {
        cout << "PASSED!" << endl << endl;
    }
    else {
        cout << "FAILED!" << endl << endl;
    }
    cout << "2) testing descending sort..." << endl;
    lst.sort(descend_compare);
    if (lst == expected_list2) {
        cout << "PASSED!" << endl << endl;
    }
    else {
        cout << "FAILED!" << endl << endl;
    }
    try {
        cout << "3) testing list with number of elements <= 1.." << endl;
        List<int> list2;
        list2.sort(ascend_compare);
    }
    catch (List_size_exception& ex){
        cout << "Error: " << ex.what() << endl;
        cout << "PASSED!" << endl << endl;
    }
    cout << "Test finished!" << endl << endl;
}

void operator_array_access_test() {
    cout << "Testing operator [] overload..." << endl;
    List<int> list1;
    list1.add(1);
    list1.add(2);
    list1.add(3);
    int b = list1[1];
    if (b == 2) {
        cout << "PASSED!" << endl << endl;
    }
    else {
        cout << "FAILED!" << endl << endl;
    }

    try {
        cout << "1) testing index < 0..." << endl;
        int b = list1[-1];
    } catch (Range_exception& ex1) {
        cout << "Error: " << ex1.what() << endl;
        cout << "PASSED!" << endl << endl;
    }

    try {
        cout << "2) testing index >= list size..." << endl;
        int b = list1[4];
    } catch (Range_exception& ex2) {
        cout << "Error: " << ex2.what() << endl;
        cout << "PASSED!" << endl << endl;
    }

    cout << "Test finished!" << endl << endl;
}

void push_front_method_test() {
    cout << "Testing push_front() method..." << endl;
    List<int> lst;
    lst.add(1);
    lst.add(2);
    lst.add(3);

    List<int> expected_lst;
    expected_lst.add(4);
    expected_lst.add(1);
    expected_lst.add(2);
    expected_lst.add(3);

    lst.push_front(4);

    if (lst == expected_lst) {
        cout << "PASSED!" << endl << endl;
    }
    else {
        cout << "FAILED!" << endl << endl;
    }
    cout << "Test finished!" << endl;
}

void pop_front_method_test() {
    cout << "Testing pop_front() method..." << endl;
    List<int> lst;
    lst.add(1);
    lst.add(2);
    lst.add(3);
    lst.pop_front();

    List<int> expected_list;
    expected_list.add(2);
    expected_list.add(3);

    if (lst == expected_list) {
        cout << "PASSED!" << endl << endl;
    }
    else {
        cout << "FAILED!" << endl << endl;
    }

    try {
        cout << "1) testing empty list..." << endl;
        List<int> list1;
        list1.pop_front();
    } catch (List_size_exception& ex) {
        cout << "Error: " << ex.what() << endl;
        cout << "PASSED!" << endl << endl;
    }
    cout << "Test finished!" << endl;
}

void reverse_method_test() {
    cout << "Testing reverse() method..." << endl;
    List<int> lst;
    lst.add(1);
    lst.add(2);
    lst.add(3);

    List<int> expected_lst;
    expected_lst.add(3);
    expected_lst.add(2);
    expected_lst.add(1);

    lst.reverse();
    if (lst == expected_lst) {
        cout << "PASSED!" << endl << endl;
    }
    else {
        cout << "FAILED!" << endl << endl;
    }
    try {
        cout << "1) Testing in empty list..." << endl;
        List<int> list1;
        list1.reverse();
    } catch (List_size_exception& ex) {
        cout << "Error: " << ex.what() << endl;
        cout << "PASSED!" << endl << endl;
    }
    cout << "Test finished!" << endl << endl;
}

void insert_after_method_test() {
    cout << "Testing insert_after_method()..." << endl;
    List<int> lst;
    lst.add(1);
    lst.add(2);
    lst.add(3);

    List<int> expected_lst;
    expected_lst.add(1);
    expected_lst.add(5);
    expected_lst.add(5);
    expected_lst.add(2);
    expected_lst.add(3);

    Iterator<int> iter(lst);
    lst.insert_after(iter, 2, 5);
    if (lst == expected_lst) {
        cout << "PASSED!" << endl << endl;
    }
    else {
        cout << "FAILED!" << endl << endl;
    }

    cout << "1) testing count = 0..." << endl;
    Iterator<int> iter_2 = lst.insert_after(iter, 0, 2);
    if (*iter_2 == lst[0]) {
        cout << "PASSED!" << endl << endl;
    }
    else {
        cout << "FAILED" << endl << endl;
    }
    cout << "Test finished!" << endl;
}








