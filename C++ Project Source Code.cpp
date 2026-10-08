#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <limits>

using namespace std;

// Formats the matrix into a clean, aligned grid
void printMatrix(const vector<vector<int>>& matrix) {
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            cout << setw(5) << matrix[i][j];
        }
        cout << endl;
    }
}

// O(N^2) Time, O(1) Space 90-Degree Clockwise Rotation
void rotateMatrix90(vector<vector<int>>& matrix) {
    int n = matrix.size();
    
    // Transpose
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            swap(matrix[i][j], matrix[j][i]);
        }
    }
    
    // Reverse
    for (int i = 0; i < n; i++) {
        reverse(matrix[i].begin(), matrix[i].end());
    }
}

// Flips the image upside down (Horizontal Axis Reflection)
void reflectHorizontal(vector<vector<int>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n / 2; i++) {
        swap(matrix[i], matrix[n - 1 - i]);
    }
}

// Flips the image left-to-right (Vertical Axis Reflection)
void reflectVertical(vector<vector<int>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; i++) {
        reverse(matrix[i].begin(), matrix[i].end());
    }
}

int main() {
    int choice;
    int n = 0;
    vector<vector<int>> imageMatrix;

    while (true) {
        cout << "\n==========================================" << endl;
        cout << "  SATELLITE IMAGE CALIBRATION UTILITY" << endl;
        cout << "==========================================" << endl;
        cout << "1. Initialize New Image Matrix" << endl;
        cout << "2. Rotate Matrix 90 Degrees" << endl;
        cout << "3. Track Specific Pixel Coordinate" << endl;
        cout << "4. Reflect Matrix (Horizontal/Vertical)" << endl;
        cout << "5. Show Complexity Proof" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        // SAFEGUARD: Check for invalid menu input
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number from the menu." << endl;
            continue;
        }

        switch (choice) {
            case 1: {
                cout << "Enter grid size N (for an N x N matrix): ";
                cin >> n;

                // SAFEGUARD: Check for invalid grid size input
                if (cin.fail() || n <= 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid size! N must be a positive integer." << endl;
                    n = 0; // Reset n so rotation can't be attempted on a failed grid
                    break;
                }

                imageMatrix.assign(n, vector<int>(n, 0));
                
                cout << "Enter the " << n * n << " pixel intensities:\n";
                bool inputFailed = false;
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        cin >> imageMatrix[i][j];
                        if (cin.fail()) {
                            inputFailed = true;
                            break;
                        }
                    }
                    if (inputFailed) break;
                }

                // SAFEGUARD: Check for invalid matrix data
                if (inputFailed) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid matrix data entered! Please re-initialize the matrix." << endl;
                    n = 0; 
                    imageMatrix.clear();
                    break;
                }

                cout << "\n--- Current Matrix ---" << endl;
                printMatrix(imageMatrix);
                break;
            }
            case 2: {
                if (n == 0) {
                    cout << "Error: Initialize a valid matrix first!" << endl;
                    break;
                }
                rotateMatrix90(imageMatrix);
                cout << "\n--- Calibrated (90-Deg Rotated) Matrix ---" << endl;
                printMatrix(imageMatrix);
                break;
            }
            case 3: {
                if (n == 0) {
                    cout << "Error: Initialize a valid matrix first!" << endl;
                    break;
                }
                int r, c;
                cout << "Enter original row index (0 to " << n-1 << "): ";
                cin >> r;
                cout << "Enter original col index (0 to " << n-1 << "): ";
                cin >> c;

                // SAFEGUARD: Catch bad coordinate inputs
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input! Coordinates must be numbers." << endl;
                    break;
                }

                if (r >= 0 && r < n && c >= 0 && c < n) {
                    pair<int, int> original = {r, c};
                    pair<int, int> rotated = {c, n - 1 - r};
                    
                    cout << "\nTransformation Log:" << endl;
                    cout << "Original Position: (" << original.first << ", " << original.second << ")" << endl;
                    cout << "New Position:      (" << rotated.first << ", " << rotated.second << ")" << endl;
                } else {
                    cout << "Coordinates out of bounds!" << endl;
                }
                break;
            }
            case 4: {
                if (n == 0) {
                    cout << "Error: Initialize a valid matrix first!" << endl;
                    break;
                }
                int refChoice;
                cout << "\nSelect Reflection Axis:\n1. Horizontal (Upside Down)\n2. Vertical (Left-to-Right)\nEnter choice: ";
                cin >> refChoice;
                
                if (cin.fail() || (refChoice != 1 && refChoice != 2)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid reflection choice!" << endl;
                    break;
                }

                if (refChoice == 1) {
                    reflectHorizontal(imageMatrix);
                    cout << "\n--- Horizontally Reflected Matrix ---" << endl;
                } else {
                    reflectVertical(imageMatrix);
                    cout << "\n--- Vertically Reflected Matrix ---" << endl;
                }
                printMatrix(imageMatrix);
                break;
            }
            case 5: {
                cout << "\nCOMPLEXITY ANALYSIS PROOF" << endl;
                cout << "- Time Complexity: O(N^2) (Transposing takes O(N^2/2), reversing takes O(N^2/2))" << endl;
                cout << "- Aux Space Complexity: O(1) (In-place transformation via swap/reverse)" << endl;
                break;
            }
            case 6:
                cout << "Exiting utility..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
}