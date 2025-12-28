#define DOCTEST_CONFIG_NO_POSIX_SIGNALS
#define DOCTEST_CONFIG_NO_MULTITHREADING
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// ANSI Color codes
#define COLOR_RESET "\033[0m"
#define COLOR_GREEN "\033[32m"
#define COLOR_RED "\033[31m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_CYAN "\033[36m"
#define COLOR_BLUE "\033[34m"
#define COLOR_BOLD "\033[1m"
#define COLOR_MAGENTA "\033[35m"

namespace totals
{
    int task1 = 0; // /30
    int task2 = 0; // /30
    int task3 = 0; // /40
}

// ===========================
// UTILITIES
// ===========================

static string toLowerCase(string s)
{
    for (char &c : s)
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    return s;
}

static string trim(const string &s)
{
    size_t a = s.find_first_not_of(" \t\r\n");
    size_t b = s.find_last_not_of(" \t\r\n");
    if (a == string::npos)
        return "";
    return s.substr(a, b - a + 1);
}

// Extract integers in order from arbitrary text
static vector<long long> extractIntegers(const string &text)
{
    vector<long long> vals;
    long long cur = 0;
    bool inNum = false, neg = false;

    auto flush = [&]
    {
        if (inNum)
        {
            vals.push_back(neg ? -cur : cur);
            cur = 0;
            neg = false;
            inNum = false;
        }
    };

    for (char ch : text)
    {
        if (!inNum && (ch == '-' || ch == '+'))
        {
            inNum = true;
            neg = (ch == '-');
            cur = 0;
        }
        else if (isdigit(static_cast<unsigned char>(ch)))
        {
            if (!inNum)
            {
                inNum = true;
                neg = false;
                cur = 0;
            }
            cur = cur * 10 + (ch - '0');
        }
        else
        {
            flush();
        }
    }
    flush();
    return vals;
}

// Split output into non-empty trimmed lines
static vector<string> splitNonEmptyLines(const string &s)
{
    vector<string> lines;
    istringstream in(s);
    string line;
    while (getline(in, line))
    {
        string trimmed = trim(line);
        if (!trimmed.empty())
            lines.push_back(trimmed);
    }
    return lines;
}

static void printTestHeader(const string &taskName, const string &caseName)
{
    cout << "\n"
         << COLOR_CYAN << COLOR_BOLD << "==========================================" << COLOR_RESET << "\n";
    cout << COLOR_CYAN << COLOR_BOLD << " " << taskName << ": " << caseName << COLOR_RESET << "\n";
    cout << COLOR_CYAN << COLOR_BOLD << "==========================================" << COLOR_RESET << "\n";
}

static void printArray(const vector<int> &arr, const string &label = "")
{
    if (!label.empty())
        cout << label << ": ";
    cout << "[ ";
    for (size_t i = 0; i < arr.size(); ++i)
    {
        cout << arr[i];
        if (i + 1 < arr.size())
            cout << ", ";
    }
    cout << " ]\n";
}

static void printMatrix(const vector<vector<int>> &m)
{
    for (const auto &row : m)
    {
        cout << "  [ ";
        for (size_t j = 0; j < row.size(); ++j)
        {
            cout << setw(3) << row[j];
            if (j + 1 < row.size())
                cout << ", ";
        }
        cout << " ]\n";
    }
}

static vector<vector<int>> diagSwapped(const vector<vector<int>> &a)
{
    vector<vector<int>> m = a;
    size_t n = m.size();
    for (size_t i = 0; i < n; ++i)
    {
        swap(m[i][i], m[i][n - 1 - i]);
    }
    return m;
}

// Check whether a contiguous sub-sequence equal to seq appears in ints
static bool containsSubsequence(const vector<long long> &ints, const vector<int> &seq)
{
    if (seq.empty() || ints.size() < seq.size())
        return false;
    for (size_t i = 0; i + seq.size() <= ints.size(); ++i)
    {
        bool ok = true;
        for (size_t k = 0; k < seq.size(); ++k)
        {
            if (ints[i + k] != seq[k])
            {
                ok = false;
                break;
            }
        }
        if (ok)
            return true;
    }
    return false;
}

static void showDiagnostics(const string &title, const string &content, int maxLines = 10)
{
    cout << "\n  " << COLOR_YELLOW << "📋 " << title << ":" << COLOR_RESET << "\n";
    auto lines = splitNonEmptyLines(content);
    int shown = min((int)lines.size(), maxLines);
    for (int i = 0; i < shown; ++i)
    {
        cout << "    " << lines[i] << "\n";
    }
    if ((int)lines.size() > maxLines)
    {
        cout << "    " << COLOR_YELLOW << "... (" << (lines.size() - maxLines) << " more lines)" << COLOR_RESET << "\n";
    }
}

// =============================================
// TASK 1: ARRAY REVERSAL (pointers-only access)
// =============================================

namespace task1_ns
{
#define main STUDENT_MAIN_TASK1
#include "task1.cpp"
#undef main

    static string runProgram(const string &input)
    {
        istringstream in(input);
        ostringstream out;
        streambuf *oldIn = cin.rdbuf(in.rdbuf());
        streambuf *oldOut = cout.rdbuf(out.rdbuf());

        try
        {
            STUDENT_MAIN_TASK1();
        }
        catch (...)
        {
            cin.rdbuf(oldIn);
            cout.rdbuf(oldOut);
            return "[PROGRAM CRASHED OR ERROR]";
        }

        cin.rdbuf(oldIn);
        cout.rdbuf(oldOut);
        return out.str();
    }

    static vector<int> reversedSegment(const vector<int> &arr, int start, int end)
    {
        vector<int> a = arr;
        reverse(a.begin() + start, a.begin() + end + 1);
        return a;
    }

    static void testCase(const string &name,
                         const vector<int> &arr,
                         int start, int end,
                         int marks,
                         int &total)
    {
        printTestHeader("Task 1", name);

        ostringstream in;
        in << arr.size() << "\n";
        for (int v : arr)
            in << v << " ";
        in << "\n"
           << start << " " << end << "\n";

        cout << COLOR_YELLOW << "Running student program..." << COLOR_RESET << endl;
        string output = runProgram(in.str());
        cout << COLOR_GREEN << "Program completed." << COLOR_RESET << endl;

        // Check if program crashed
        if (output == "[PROGRAM CRASHED OR ERROR]")
        {
            cout << "\n"
                 << COLOR_RED << COLOR_BOLD << "⚠ CRITICAL ERROR:" << COLOR_RESET << "\n";
            cout << "  Your program crashed or encountered a runtime error!\n";
            cout << "\n  " << COLOR_MAGENTA << "💡 Common causes:" << COLOR_RESET << "\n";
            cout << "     • Segmentation fault (accessing invalid memory)\n";
            cout << "     • Infinite loop in your code\n";
            cout << "     • Array out of bounds access\n";
            cout << "     • Invalid pointer operations\n";
            cout << "\n"
                 << COLOR_BOLD << "Marks Earned: " << COLOR_RED << "0"
                 << COLOR_RESET << " / " << marks << "\n";
            INFO("[Task1] " << name << " - Program crashed");
            CHECK(false);
            return;
        }

        auto ints = extractIntegers(output);
        vector<int> expected = reversedSegment(arr, start, end);

        cout << COLOR_BOLD << "Input:" << COLOR_RESET << "\n";
        printArray(arr, "  Original array");
        cout << "  Segment to reverse: [" << start << ", " << end << "]\n";

        cout << "\n"
             << COLOR_BOLD << "Expected Output:" << COLOR_RESET << "\n";
        printArray(expected, "  Reversed array");

        bool found = containsSubsequence(ints, expected);

        cout << "\n"
             << COLOR_BOLD << "Test Results:" << COLOR_RESET << "\n";
        if (found)
        {
            cout << "  " << COLOR_GREEN << "✓ [PASS]" << COLOR_RESET << " Correct reversed array found in output\n";
            total += marks;

            cout << "\n"
                 << COLOR_BOLD << "Marks Earned: " << COLOR_GREEN << marks
                 << COLOR_RESET << " / " << marks << "\n";
        }
        else
        {
            cout << "  " << COLOR_RED << "✗ [FAIL]" << COLOR_RESET << " Expected array not found in output\n";

            // Detailed diagnostics
            cout << "\n  " << COLOR_YELLOW << "Expected array:" << COLOR_RESET << "\n    ";
            for (size_t i = 0; i < expected.size(); ++i)
            {
                cout << expected[i];
                if (i + 1 < expected.size())
                    cout << ", ";
            }
            cout << "\n";

            if (ints.size() >= expected.size())
            {
                cout << "\n  " << COLOR_YELLOW << "Integers found in your output:" << COLOR_RESET << "\n    ";
                for (size_t i = 0; i < min(ints.size(), (size_t)15); ++i)
                {
                    cout << ints[i];
                    if (i + 1 < min(ints.size(), (size_t)15))
                        cout << ", ";
                }
                if (ints.size() > 15)
                    cout << " ...";
                cout << "\n";

                // Check if original array is there (not reversed)
                if (containsSubsequence(ints, arr))
                {
                    cout << "\n  " << COLOR_RED << "⚠ Found original array (not reversed) in output" << COLOR_RESET << "\n";
                    cout << "    → Array reversal was NOT performed\n";
                }
            }
            else
            {
                cout << "\n  " << COLOR_RED << "⚠ Your output has too few numbers" << COLOR_RESET << "\n";
                cout << "    Expected at least: " << expected.size() << " numbers\n";
                cout << "    Found: " << ints.size() << " numbers\n";
            }

            showDiagnostics("Your Program Output", output, 8);

            cout << "\n  " << COLOR_MAGENTA << "💡 Deduction Reason:" << COLOR_RESET << "\n";
            cout << "     ✗ Reversed array not found in output\n";
            cout << "\n  " << COLOR_MAGENTA << "Common Issues:" << COLOR_RESET << "\n";
            cout << "     • Not reversing the segment correctly\n";
            cout << "     • Wrong pointer arithmetic\n";
            cout << "     • Not printing the array after reversal\n";
            cout << "     • Reversing wrong indices\n";

            cout << "\n"
                 << COLOR_BOLD << "Marks Earned: " << COLOR_RED << "0"
                 << COLOR_RESET << " / " << marks << "\n";
        }

        INFO("[Task1] " << name);
        CHECK(found);
    }
}

// =============================================
// TASK 2: SWAP DIAGONALS
// =============================================

namespace task2_ns
{
#define main STUDENT_MAIN_TASK2
#include "task2.cpp"
#undef main

    static string runProgram(const string &input)
    {
        istringstream in(input);
        ostringstream out;
        streambuf *oldIn = cin.rdbuf(in.rdbuf());
        streambuf *oldOut = cout.rdbuf(out.rdbuf());

        try
        {
            STUDENT_MAIN_TASK2();
        }
        catch (...)
        {
            cin.rdbuf(oldIn);
            cout.rdbuf(oldOut);
            return "[PROGRAM CRASHED OR ERROR]";
        }

        cin.rdbuf(oldIn);
        cout.rdbuf(oldOut);
        return out.str();
    }

    static vector<long long> flatten(const vector<vector<int>> &m)
    {
        vector<long long> f;
        for (auto &r : m)
            for (int v : r)
                f.push_back(v);
        return f;
    }

    static bool outputContainsMatrix(const string &out, const vector<vector<int>> &m)
    {
        vector<long long> ints = extractIntegers(out);
        vector<long long> seq = flatten(m);
        if (ints.size() < seq.size())
            return false;
        for (size_t i = 0; i + seq.size() <= ints.size(); ++i)
        {
            bool ok = true;
            for (size_t k = 0; k < seq.size(); ++k)
            {
                if (ints[i + k] != seq[k])
                {
                    ok = false;
                    break;
                }
            }
            if (ok)
                return true;
        }
        return false;
    }

    static void testCase(const string &name,
                         const vector<vector<int>> &matrix,
                         int marksPerCheck,
                         int &total)
    {
        printTestHeader("Task 2", name);

        int n = (int)matrix.size();
        auto swapped = diagSwapped(matrix);

        ostringstream in;
        in << n << "\n";
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                in << matrix[i][j] << "\n";
        in << "-1\n";

        string out = runProgram(in.str());

        cout << COLOR_BOLD << "Input Matrix (" << n << "×" << n << "):" << COLOR_RESET << "\n";
        ::printMatrix(matrix);

        cout << "\n"
             << COLOR_BOLD << "Expected After Diagonal Swap:" << COLOR_RESET << "\n";
        cout << "  (Swap main diagonal ↔ anti-diagonal)\n";
        ::printMatrix(swapped);

        bool originalPrinted = outputContainsMatrix(out, matrix);
        bool swappedPrinted = outputContainsMatrix(out, swapped);

        int earned = 0;

        cout << "\n"
             << COLOR_BOLD << "Test Results:" << COLOR_RESET << "\n";

        // Check 1: Original Matrix Display
        if (originalPrinted)
        {
            cout << "  " << COLOR_GREEN << "✓ [PASS]" << COLOR_RESET
                 << " Original matrix displayed correctly (+" << marksPerCheck / 2 << " marks)\n";
            earned += marksPerCheck / 2;
        }
        else
        {
            cout << "  " << COLOR_RED << "✗ [FAIL]" << COLOR_RESET
                 << " Original matrix NOT found in output (-" << marksPerCheck / 2 << " marks)\n";
        }

        // Check 2: Swapped Matrix Display
        if (swappedPrinted)
        {
            cout << "  " << COLOR_GREEN << "✓ [PASS]" << COLOR_RESET
                 << " Swapped matrix displayed correctly (+" << (marksPerCheck - marksPerCheck / 2) << " marks)\n";
            earned += marksPerCheck - (marksPerCheck / 2);
        }
        else
        {
            cout << "  " << COLOR_RED << "✗ [FAIL]" << COLOR_RESET
                 << " Swapped matrix NOT found in output (-" << (marksPerCheck - marksPerCheck / 2) << " marks)\n";
        }

        // Detailed diagnostics if something failed
        if (!originalPrinted || !swappedPrinted)
        {
            auto ints = extractIntegers(out);
            cout << "\n  " << COLOR_YELLOW << "Integers extracted from your output:" << COLOR_RESET << "\n    ";
            for (size_t i = 0; i < min(ints.size(), (size_t)25); ++i)
            {
                cout << ints[i];
                if (i + 1 < min(ints.size(), (size_t)25))
                    cout << ", ";
            }
            if (ints.size() > 25)
                cout << " ...";
            cout << "\n";

            showDiagnostics("Your Program Output", out, 12);

            cout << "\n  " << COLOR_MAGENTA << "💡 Deduction Reasons:" << COLOR_RESET << "\n";
            if (!originalPrinted)
            {
                cout << "     ✗ Original matrix not displayed before swap\n";
            }
            if (!swappedPrinted)
            {
                cout << "     ✗ Swapped matrix not displayed or swap logic incorrect\n";
            }

            cout << "\n  " << COLOR_MAGENTA << "Common Issues:" << COLOR_RESET << "\n";
            if (!originalPrinted && !swappedPrinted)
            {
                cout << "     • Matrix not being read or displayed at all\n";
                cout << "     • Wrong input reading logic\n";
                cout << "     • Not printing any matrix\n";
            }
            else if (!originalPrinted)
            {
                cout << "     • Skipping original matrix display\n";
                cout << "     • Only printing final result\n";
            }
            else if (!swappedPrinted)
            {
                cout << "     • Diagonal swap logic is incorrect\n";
                cout << "     • Swapping wrong elements (should swap [i][i] ↔ [i][n-1-i])\n";
                cout << "     • Not displaying matrix after swap\n";
                cout << "     • Modifying wrong diagonals\n";
            }
        }

        total += earned;

        cout << "\n"
             << COLOR_BOLD << "Result: ";
        if (earned == marksPerCheck)
        {
            cout << COLOR_GREEN << "FULL MARKS" << COLOR_RESET;
        }
        else if (earned > 0)
        {
            cout << COLOR_YELLOW << "PARTIAL CREDIT" << COLOR_RESET;
        }
        else
        {
            cout << COLOR_RED << "NO MARKS" << COLOR_RESET;
        }
        cout << " | Marks Earned: ";
        if (earned == marksPerCheck)
        {
            cout << COLOR_GREEN << earned << COLOR_RESET;
        }
        else if (earned > 0)
        {
            cout << COLOR_YELLOW << earned << COLOR_RESET;
        }
        else
        {
            cout << COLOR_RED << earned << COLOR_RESET;
        }
        cout << " / " << marksPerCheck << "\n";

        INFO("[Task2] " << name);
        CHECK(originalPrinted);
        CHECK(swappedPrinted);
    }
}

// =============================================
// TASK 3: WORD PROCESSING (reverse printing)
// =============================================

namespace task3_ns
{
#define main STUDENT_MAIN_TASK3
#include "task3.cpp"
#undef main

    static string runProgram(const string &input)
    {
        istringstream in(input);
        ostringstream out;
        streambuf *oldIn = cin.rdbuf(in.rdbuf());
        streambuf *oldOut = cout.rdbuf(out.rdbuf());

        try
        {
            STUDENT_MAIN_TASK3();
        }
        catch (...)
        {
            cin.rdbuf(oldIn);
            cout.rdbuf(oldOut);
            return "[PROGRAM CRASHED OR ERROR]";
        }

        cin.rdbuf(oldIn);
        cout.rdbuf(oldOut);
        return out.str();
    }

    // Flexible matching: check if lines appear in reverse order
    static pair<int, vector<bool>> checkReversedOrder(const string &out, const vector<string> &inputLines)
    {
        vector<string> expected;
        for (auto it = inputLines.rbegin(); it != inputLines.rend(); ++it)
        {
            expected.push_back(toLowerCase(trim(*it)));
        }

        auto outLines = splitNonEmptyLines(out);
        vector<string> outLower;
        for (const auto &l : outLines)
            outLower.push_back(toLowerCase(l));

        vector<bool> found(expected.size(), false);
        size_t j = 0;

        for (const string &outLine : outLower)
        {
            if (j < expected.size())
            {
                if (outLine.find(expected[j]) != string::npos)
                {
                    found[j] = true;
                    ++j;
                }
            }
        }

        return {j, found}; // return count of correctly ordered lines
    }

    static void testCase(const string &name,
                         const vector<string> &inputLines,
                         int marksPerCase,
                         int &total)
    {
        printTestHeader("Task 3", name);

        ostringstream in;
        for (const auto &L : inputLines)
            in << L << "\n";

        vector<string> expected;
        for (auto it = inputLines.rbegin(); it != inputLines.rend(); ++it)
            expected.push_back(*it);

        string out = runProgram(in.str());

        cout << COLOR_BOLD << "Input Lines (in order):" << COLOR_RESET << "\n";
        for (size_t i = 0; i < inputLines.size(); ++i)
        {
            cout << "  " << (i + 1) << ". \"" << inputLines[i] << "\"\n";
        }

        cout << "\n"
             << COLOR_BOLD << "Expected Output (reversed order):" << COLOR_RESET << "\n";
        for (size_t i = 0; i < expected.size(); ++i)
        {
            cout << "  " << (i + 1) << ". \"" << expected[i] << "\"\n";
        }

        auto [correctCount, foundFlags] = checkReversedOrder(out, inputLines);
        bool allCorrect = (correctCount == (int)expected.size());

        // Calculate partial marks based on correct lines
        int earned = (correctCount * marksPerCase) / (int)expected.size();

        cout << "\n"
             << COLOR_BOLD << "Test Results:" << COLOR_RESET << "\n";

        if (allCorrect)
        {
            cout << "  " << COLOR_GREEN << "✓ [PASS]" << COLOR_RESET
                 << " All lines printed in correct reverse order (+" << marksPerCase << " marks)\n";
            earned = marksPerCase;
        }
        else
        {
            cout << "  " << COLOR_YELLOW << "⚠ [PARTIAL]" << COLOR_RESET
                 << " " << correctCount << " out of " << expected.size()
                 << " lines correct in reverse order\n";

            cout << "\n  " << COLOR_YELLOW << "Line-by-line analysis:" << COLOR_RESET << "\n";
            for (size_t i = 0; i < expected.size(); ++i)
            {
                if (foundFlags[i])
                {
                    cout << "    " << COLOR_GREEN << "✓" << COLOR_RESET;
                }
                else
                {
                    cout << "    " << COLOR_RED << "✗" << COLOR_RESET;
                }
                cout << " Position " << (i + 1) << ": \"" << expected[i] << "\"";
                if (!foundFlags[i])
                    cout << " " << COLOR_RED << "(NOT FOUND IN CORRECT POSITION)" << COLOR_RESET;
                cout << "\n";
            }

            showDiagnostics("Your Program Output", out, 10);

            cout << "\n  " << COLOR_MAGENTA << "💡 Deduction Reasons:" << COLOR_RESET << "\n";
            cout << "     ✗ Only " << correctCount << "/" << expected.size()
                 << " lines printed in correct reverse order\n";
            for (size_t i = 0; i < expected.size(); ++i)
            {
                if (!foundFlags[i])
                {
                    cout << "     ✗ Line \"" << expected[i] << "\" not found at position " << (i + 1) << "\n";
                }
            }

            cout << "\n  " << COLOR_MAGENTA << "Common Issues:" << COLOR_RESET << "\n";
            cout << "     • Lines not being printed in complete reverse order\n";
            cout << "     • Some lines missing from output\n";
            cout << "     • Incorrect recursion or stack implementation\n";
            cout << "     • Reading lines incorrectly\n";
            cout << "     • Lines printed in wrong order\n";
        }

        total += earned;

        cout << "\n"
             << COLOR_BOLD << "Result: ";
        if (allCorrect)
        {
            cout << COLOR_GREEN << "FULL MARKS" << COLOR_RESET;
        }
        else if (earned > 0)
        {
            cout << COLOR_YELLOW << "PARTIAL CREDIT (" << correctCount << "/" << expected.size() << " correct)" << COLOR_RESET;
        }
        else
        {
            cout << COLOR_RED << "NO MARKS" << COLOR_RESET;
        }
        cout << " | Marks Earned: ";
        if (allCorrect)
        {
            cout << COLOR_GREEN << earned << COLOR_RESET;
        }
        else if (earned > 0)
        {
            cout << COLOR_YELLOW << earned << COLOR_RESET;
        }
        else
        {
            cout << COLOR_RED << earned << COLOR_RESET;
        }
        cout << " / " << marksPerCase << "\n";

        INFO("[Task3] " << name);
        CHECK(allCorrect);
    }
}

// ===========================
// TEST SUITE
// ===========================

TEST_CASE("Task 1: Array Reversal (30 marks)")
{
    int marks = 0;

    cout << "\n"
         << COLOR_BOLD << COLOR_BLUE
         << "============================================================" << COLOR_RESET << "\n";
    cout << COLOR_BOLD << COLOR_BLUE << "  TASK 1: ARRAY REVERSAL (30 marks)" << COLOR_RESET << "\n";
    cout << COLOR_BOLD << COLOR_BLUE
         << "============================================================" << COLOR_RESET << "\n";

    task1_ns::testCase("Middle segment", {1, 2, 3, 4, 5, 6, 7, 8}, 2, 6, 10, marks);
    task1_ns::testCase("Prefix segment", {10, 20, 30, 40, 50}, 0, 2, 10, marks);
    task1_ns::testCase("Suffix segment", {9, 8, 7, 6, 5}, 2, 4, 10, marks);

    cout << "\n"
         << COLOR_BOLD << COLOR_BLUE
         << "============================================================" << COLOR_RESET << "\n";
    cout << COLOR_BOLD << "TASK 1 TOTAL: " << COLOR_GREEN << marks << COLOR_RESET << " / 30\n";
    cout << COLOR_BOLD << COLOR_BLUE
         << "============================================================" << COLOR_RESET << "\n";

    totals::task1 = marks;
}

TEST_CASE("Task 2: Swap Diagonals (30 marks)")
{
    int marks = 0;

    cout << "\n"
         << COLOR_BOLD << COLOR_BLUE
         << "============================================================" << COLOR_RESET << "\n";
    cout << COLOR_BOLD << COLOR_BLUE << "  TASK 2: SWAP DIAGONALS (30 marks)" << COLOR_RESET << "\n";
    cout << COLOR_BOLD << COLOR_BLUE
         << "============================================================" << COLOR_RESET << "\n";

    task2_ns::testCase("3x3 basic", {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, 15, marks);
    task2_ns::testCase("5x5 varied",
                       {{1, 2, 3, 4, 5},
                        {6, 7, 8, 9, 10},
                        {11, 12, 13, 14, 15},
                        {16, 17, 18, 19, 20},
                        {21, 22, 23, 24, 25}},
                       15, marks);

    cout << "\n"
         << COLOR_BOLD << COLOR_BLUE
         << "============================================================" << COLOR_RESET << "\n";
    cout << COLOR_BOLD << "TASK 2 TOTAL: " << COLOR_GREEN << marks << COLOR_RESET << " / 30\n";
    cout << COLOR_BOLD << COLOR_BLUE
         << "============================================================" << COLOR_RESET << "\n";

    totals::task2 = marks;
}

TEST_CASE("Task 3: Word Processing (40 marks)")
{
    int marks = 0;

    cout << "\n"
         << COLOR_BOLD << COLOR_BLUE
         << "============================================================" << COLOR_RESET << "\n";
    cout << COLOR_BOLD << COLOR_BLUE << "  TASK 3: WORD PROCESSING (40 marks)" << COLOR_RESET << "\n";
    cout << COLOR_BOLD << COLOR_BLUE
         << "============================================================" << COLOR_RESET << "\n";

    task3_ns::testCase("Three short lines", {"alpha", "beta", "gamma", "END"}, 20, marks);
    task3_ns::testCase("Spaces & punctuation", {"hello world", "CS100!", "pointers > arrays", "END"}, 20, marks);

    cout << "\n"
         << COLOR_BOLD << COLOR_BLUE
         << "============================================================" << COLOR_RESET << "\n";
    cout << COLOR_BOLD << "TASK 3 TOTAL: " << COLOR_GREEN << marks << COLOR_RESET << " / 40\n";
    cout << COLOR_BOLD << COLOR_BLUE
         << "============================================================" << COLOR_RESET << "\n";

    totals::task3 = marks;
}

TEST_CASE("Overall Score (100 marks)")
{
    int total = totals::task1 + totals::task2 + totals::task3;

    cout << "\n"
         << COLOR_BOLD << COLOR_CYAN
         << "============================================================" << COLOR_RESET << "\n";
    cout << COLOR_BOLD << COLOR_CYAN << "              FINAL LAB RESULTS" << COLOR_RESET << "\n";
    cout << COLOR_BOLD << COLOR_CYAN
         << "============================================================" << COLOR_RESET << "\n";
    cout << COLOR_BOLD << "Overall Score: " << COLOR_GREEN << total << COLOR_RESET << " / 100\n\n";
    cout << "Breakdown:\n";
    cout << "  Task 1 (Array Reversal):  " << COLOR_GREEN << totals::task1 << COLOR_RESET << " / 30\n";
    cout << "  Task 2 (Swap Diagonals):  " << COLOR_GREEN << totals::task2 << COLOR_RESET << " / 30\n";
    cout << "  Task 3 (Word Processing): " << COLOR_GREEN << totals::task3 << COLOR_RESET << " / 40\n";
    cout << COLOR_BOLD << COLOR_CYAN
         << "============================================================" << COLOR_RESET << "\n";

    CHECK(total <= 100);
}

int main(int argc, char **argv)
{
    cout << COLOR_BOLD << COLOR_CYAN
         << "\n============================================================\n";
    cout << "          CS100 LAB 11 - TEST SUITE                 \n";
    cout << "      Pointers and 2D Arrays (Fall 2025)            \n";
    cout << "============================================================" << COLOR_RESET << "\n\n";

    cout << COLOR_YELLOW << "📁 Checking for required files..." << COLOR_RESET << "\n";
    cout << "   • task1.cpp ... ";
#ifdef STUDENT_MAIN_TASK1
    cout << COLOR_GREEN << "✓ Found" << COLOR_RESET << "\n";
#else
    cout << COLOR_RED << "✗ Not found" << COLOR_RESET << "\n";
#endif

    cout << "   • task2.cpp ... ";
#ifdef STUDENT_MAIN_TASK2
    cout << COLOR_GREEN << "✓ Found" << COLOR_RESET << "\n";
#else
    cout << COLOR_RED << "✗ Not found" << COLOR_RESET << "\n";
#endif

    cout << "   • task3.cpp ... ";
#ifdef STUDENT_MAIN_TASK3
    cout << COLOR_GREEN << "✓ Found" << COLOR_RESET << "\n";
#else
    cout << COLOR_RED << "✗ Not found" << COLOR_RESET << "\n";
#endif
    cout << "\n";

    cout << COLOR_BOLD << "Select test to run:" << COLOR_RESET << "\n";
    cout << "  1. Task 1 - Array Reversal (30)\n";
    cout << "  2. Task 2 - Swap Diagonals (30)\n";
    cout << "  3. Task 3 - Word Processing (40)\n";
    cout << "  4. Run All Tests (100)\n";
    cout << "\n"
         << COLOR_YELLOW << "Enter choice (1-4): " << COLOR_RESET;

    string choice;
    if (!getline(cin, choice))
        choice = "4";

    doctest::Context ctx;
    ctx.addFilter("reporters", "console");
    ctx.setOption("success", false);
    ctx.setOption("no-breaks", true);
    ctx.setOption("no-skip", true);
    ctx.setOption("abort-after", 0);

    if (choice == "1")
    {
        ctx.addFilter("test-case", "Task 1*");
    }
    else if (choice == "2")
    {
        ctx.addFilter("test-case", "Task 2*");
    }
    else if (choice == "3")
    {
        ctx.addFilter("test-case", "Task 3*");
    }

    cout << "\n"
         << COLOR_CYAN << "============================================================" << COLOR_RESET << "\n";
    cout << COLOR_YELLOW << "Starting tests..." << COLOR_RESET << "\n";
    cout << COLOR_CYAN << "============================================================" << COLOR_RESET << "\n";

    int result = ctx.run();

    cout << "\n"
         << COLOR_CYAN << "============================================================" << COLOR_RESET << "\n";
    cout << COLOR_GREEN << "Testing complete!" << COLOR_RESET << "\n";
    cout << COLOR_CYAN << "============================================================" << COLOR_RESET << "\n\n";

    return result;
}