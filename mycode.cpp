#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <streambuf>

using namespace std;
using namespace std::chrono;

class Attendance;
class Student;
class Course;
class Date;

// User Class
class User
{
protected:
    string username;
    string password;
    bool loginStatus;
    int index;

public:
    User()
    {
        username = "";
        password = "";
        loginStatus = false;
    }

    User(string user, string pass)
    {
        username = user;
        password = pass;
        loginStatus = false;
        index = 0;
    }

    string getUsername()
    {
        return username;
    }

    string getPassword()
    {
        return password;
    }

    bool getLoginStatus()
    {
        return loginStatus;
    }

    int getIndex()
    {
        return index;
    }

    void setUsername(string user)
    {
        int i = 0;
        username = user;
        while (username[i] != '\0')
        {
            if (username[i] == ' ')
            {
                username[i] = '.';
            }

            else if (user[i] >= 'A' && user[i] <= 'Z')
            {
                username[i] = username[i] + 32;
            }

            else
            {
                username[i] = username[i];
            }
            i++;
        }
    }

    void setPassword(string pass)
    {
        password = pass;
    }

    bool loginStudent()
    {
        ifstream credentials;
        credentials.open("CredentialsStudents.csv");

        if (!credentials.is_open())
        {
            cout << "Error opening credentials file." << endl;
            return false;
        }

        string line;
        const int ROWS = 216;
        int row = 0;
        bool userStatus;
        bool passwordStatus;
        int temp = -1;

        while (getline(credentials, line))
        {
            userStatus = false;
            passwordStatus = false;

            if (row >= ROWS)
            {
                break;
            }

            stringstream lineStream(line);
            string cell;
            int column = 0;

            while (getline(lineStream, cell, ','))
            {
                if (column >= 216)
                {
                    break;
                }

                if (column == 0)
                {
                    if (cell == username)
                    {
                        userStatus = true;
                        temp = row;
                    }

                    else
                    {
                        userStatus = false;
                    }
                }

                if (column == 1)
                {
                    if (cell == password && userStatus == true)
                    {
                        passwordStatus = true;
                        temp = row;
                    }

                    else
                    {
                        passwordStatus = false;
                    }
                }

                column++;
            }

            if (userStatus && passwordStatus)
            {
                loginStatus = true;
                index = row;
                return true;
            }

            row++;
        }

        return false;
    }

    bool loginTeacher()
    {
        ifstream credentials;
        credentials.open("CredentialsTeacher.csv");

        if (!credentials.is_open())
        {
            cout << "Error opening credentials file." << endl;
            return false;
        }

        string line;
        const int ROWS = 11;
        int row = 0;
        bool userStatus;
        bool passwordStatus;
        int temp = -1;

        while (getline(credentials, line))
        {
            userStatus = false;
            passwordStatus = false;

            if (row >= ROWS)
            {
                cout << "Maximum number of rows exceeded!" << endl;
                break;
            }

            stringstream lineStream(line);
            string cell;
            int column = 0;

            while (getline(lineStream, cell, ','))
            {
                if (column >= 219)
                {
                    cout << "Maximum number of columns exceeded!" << endl;
                    break;
                }

                if (column == 0)
                {
                    if (cell == username)
                    {
                        userStatus = true;
                        temp = row;
                    }

                    else
                    {
                        userStatus = false;
                    }
                }

                if (column == 1)
                {
                    if (cell == password && userStatus == true)
                    {
                        passwordStatus = true;
                        temp = row;
                    }

                    else
                    {
                        passwordStatus = false;
                    }
                }

                column++;
            }

            if (userStatus && passwordStatus)
            {
                loginStatus = true;
                return true;
            }

            row++;
        }

        return false;
    }

    bool registerStudent()
    {
        ofstream credentials;
        credentials.open("CredentialsStudents.csv", ios::app);

        if (!credentials.is_open())
        {
            cout << "Error opening credentials file." << endl;
            return 0;
        }

        credentials << username << "," << password << endl;

        credentials.close();
        return true;
    }

    bool registerTeacher()
    {
        ofstream credentials;
        credentials.open("CredentialsTeacher.csv", ios::app);

        if (!credentials.is_open())
        {
            cout << "Error opening credentials file." << endl;
            return 0;
        }

        credentials << username << "," << password << endl;

        credentials.close();
        return true;
    }

    void logout()
    {
        if (loginStatus == true)
        {
            loginStatus = false;
        }
    }
};

// Teacher Class
class Teacher : public User
{
    string name;

public:
    Teacher() : User()
    {
        name = "";
    }

    Teacher(string name, string user, string pass, string id) : User(user, pass)
    {
        name = name;
    }

    void setName(string name)
    {
        this->name = name;
    }

    string getName()
    {
        return name;
    }

    friend ostream &operator<<(ostream &, Teacher);
};

ostream &operator<<(ostream &out, Teacher T)
{
    out << "\nTeacher Name: " << T.getName();

    return out;
}

// Student Class
class Student : public User
{
    int serial;
    string name;
    string rollNo;
    int courseCount;
    int *missedClasses;
    int *attended;
    float *percentage;
    int *totalClasses;

public:
    Student() : User()
    {
        serial = 0;
        name = "";
        rollNo = "";
        courseCount = 0;
        // attendance = new Attendance();
    }

    Student(int serial, string name, string roll, string user, string pass, Course *c, int count) : User(user, pass)
    {
        this->serial = serial;
        this->name = name;
        rollNo = roll;
        courseCount = count;
    }

    int getSerial()
    {
        return serial;
    }

    string getName()
    {
        return name;
    }

    string getRollNo()
    {
        return rollNo;
    }

    int getCourseCount()
    {
        return courseCount;
    }

    int getMissedClasses(int index)
    {
        return missedClasses[index];
    }

    int getTotalClasses(int index)
    {
        return totalClasses[index];
    }

    int getAttendedClasses(int index)
    {
        return attended[index];
    }

    float getPercentage(int index)
    {
        return percentage[index];
    }

    // Attendance getAttendance()
    // {
    //     return attendance;
    // }

    void setSerial(string serial)
    {
        int temp, result = 0;
        int i = 0;

        while (serial[i] != '\0')
        {
            i++;
        }

        for (int j = 0; j < i; j++)
        {
            if (serial[j] >= '0' && serial[j] <= '9')
            {
                temp = serial[j] - 48;
                result = result * 10 + temp;
            }
        }
        this->serial = result;
    }

    void setName(string name)
    {
        this->name = name;
    }

    void setRollNo(string roll)
    {
        rollNo = roll;
    }

    void setCourseCount(int count)
    {
        courseCount = count;
    }

    void setTotalClasses(int count, int index)
    {
        totalClasses = new int[11];

        totalClasses[index] = count;
    }

    void setMissed(int count, int index)
    {
        missedClasses = new int[totalClasses[index]];
        missedClasses[index] = count;
    }

    void setAttendedClasses(int index)
    {
        attended = new int[totalClasses[index]];
        attended[index] = totalClasses[index] - missedClasses[index];
    }

    void setPercentage(int index)
    {
        percentage = new float[totalClasses[index]];

        percentage[index] = ((float)attended[index] / totalClasses[index]) * 100;
    }

    void displayStudent()
    {
        cout << name << " - " << rollNo << endl;
    }

    bool operator==(Student &S)
    {
        if (name == S.name && rollNo == S.rollNo)
        {
            return true;
        }

        return false;
    }

    friend ostream &operator<<(ostream &out, Student &S)
    {
        out << S.getName() << " - " << S.getRollNo();
        return out;
    }

    // ~Student()
    // {
    //     delete[] totalClasses;
    //     delete[] missedClasses;
    //     delete[] attended;
    //     delete[] percentage;
    // }
};

class Date
{
    int day;
    int month;
    int year;

public:
    Date()
    {
        day = 0;
        month = 0;
        year = 0;
    }

    Date(int day, int month, int year)
    {
        this->day = day;
        this->month = month;
        this->year = year;
    }

    int getDay()
    {
        return day;
    }

    int getMonth()
    {
        return month;
    }

    int getYear()
    {
        return year;
    }

    string getDate()
    {
        string date;
        date += to_string(day);
        date += "-";
        date += to_string(month);
        date += "-";
        date += to_string(year);

        return date;
    }

    void setDay(int day)
    {
        this->day = day;
    }

    void setMonth(int month)
    {
        this->month = month;
    }

    void setYear(int year)
    {
        this->year = year;
    }

    void showDate()
    {
        cout << day << "-" << month << "-" << year;
    }

    friend ostream &operator<<(ostream &out, Date &D);
};

ostream &operator<<(ostream &out, Date &D)
{
    out << D.getDay() << "-" << D.getMonth() << "-" << D.getYear();

    return out;
}

class Attendance
{
    int totalStudents;
    int totalClasses;
    int **attendedClasses;
    int missedClasses;
    float attendancePercentage;
    Date *classDate;
    Student *student;

public:
    Attendance()
    {
        totalClasses = 1;
        attendedClasses = 0;
        missedClasses = 0;
        attendancePercentage = 0;
        totalStudents = 1;

        classDate = new Date[totalClasses];
        student = new Student[totalStudents];
        attendedClasses = new int *[totalStudents];
        for (int i = 0; i < totalStudents; i++)
        {
            attendedClasses[i] = new int[totalClasses];
        }
    }

    Attendance(int totalStudents, int totalClasses)
    {
        this->totalStudents = totalStudents;
        this->totalClasses = totalClasses;

        attendedClasses = new int *[totalClasses];
        for (int i = 0; i < totalClasses; i++)
        {
            attendedClasses[i] = new int[totalStudents];
        }

        missedClasses = 0;
        attendancePercentage = 0.0;

        classDate = new Date[totalClasses];
        student = new Student[totalStudents];
    }

    int getTotalClasses()
    {
        return totalClasses;
    }

    int getAttendedClasses(int i, int j)
    {
        return attendedClasses[i][j];
    }

    int getMissedClasses()
    {
        return missedClasses;
    }

    Date *getClassDate()
    {
        return classDate;
    }

    Student *getStudent(int i)
    {
        return student;
    }

    void setTotalClasses(int total)
    {
        totalClasses = total;
    }

    void setMissedClasses(int missed)
    {
        missedClasses = missed;
    }

    void setAttendancePercentage(float attendance)
    {
        attendancePercentage = attendance;
    }

    void setClassDate(Date *date)
    {
        classDate = date;
    }

    void setStudent(Student *student)
    {
        this->student = student;
    }

    void setTotalStudents(int count)
    {
        totalStudents = count;
    }

    void setTotalCLasses(int count)
    {
        totalClasses = count;
    }

    void setAttendance(Date *D, Student *S)
    {
        classDate = D;
        student = S;

        cout << "\n(1: Present, 0: Absent)";
        for (int i = 0; i < totalClasses; ++i)
        {
            for (int j = 0; j < totalStudents; ++j)
            {
                cout << "\n"
                     << j + 1 << ". " << student[j].getName() << " on ";
                classDate[i].showDate();
                cout << " : ";

                cin >> attendedClasses[i][j];
            }

            cout << "\n\t\t---------\n";
        }
    }

    void setNewAttendance(Date D, Student *S)
    {
        int i = 0;
        for (int j = 0; j < totalStudents; j++)
        {
            cout << "\n"
                 << j + 1 << ". " << S[j].getName() << " on ";
            D.showDate();
            cout << " : ";

            cin >> attendedClasses[i][j];
        }

        totalClasses++;
    }

    void write(string courseName)
    {
        ofstream file(courseName);
        if (!file)
        {
            cout << "Error opening file." << endl;
            return;
        }

        file << "Date,";

        for (int i = 0; i < totalClasses; ++i)
        {
            file << classDate[i];
            if (i != totalClasses - 1)
            {
                file << " , ";
            }
        }

        file << "\n";

        for (int i = 0; i < totalStudents; ++i)
        {
            file << student[i].getName() << ",";

            for (int j = 0; j < totalClasses; ++j)
            {
                file << attendedClasses[j][i];
                if (j != totalClasses - 1)
                {
                    file << " , ";
                }
            }
            file << "\n";
        }

        file.close();
    }

    void addAttendance(string courseName, Date D)
    {
        // Open the original CSV file for reading
        ifstream readFile(courseName);

        if (!readFile)
        {
            cout << "Error opening file." << endl;
            return;
        }

        // Create a temporary file to store the updated attendance data
        ofstream tempFile("temp.csv");

        if (!tempFile)
        {
            cout << "Error creating temporary file." << endl;
            readFile.close();
            return;
        }

        // Copy the existing attendance data to the temporary file
        string line;
        while (getline(readFile, line))
        {
            tempFile << line << endl;
        }

        // Close the original and temporary files
        readFile.close();
        tempFile.close();

        // Open the original CSV file in write mode
        ofstream writeFile(courseName);

        if (!writeFile)
        {
            cout << "Error opening file." << endl;
            return;
        }

        // Copy the attendance data from the temporary file to the original file row by row
        ifstream tempReadFile("temp.csv");
        string tempLine;
        int lineCount = 0;

        while (getline(tempReadFile, tempLine))
        {
            if (tempLine.empty())
            {
                // Write the new date in the last header cell
                writeFile << D.getDate() << endl;
            }
            else
            {
                // Write the existing attendance data to the original file
                writeFile << tempLine;

                // Write the new attendance for the last column
                if (lineCount == 0)
                {
                    writeFile << "," << D.getDate(); // Write the new date in the last column header
                }
                else
                {
                    writeFile << "," << attendedClasses[0][lineCount - 1]; // Assuming each date has 2 columns (attended and missed)
                }

                writeFile << endl;
            }

            lineCount++;
        }

        // Close the original and temporary files
        tempReadFile.close();
        writeFile.close();

        // Remove the temporary file
        remove("temp.csv");
    }

    void displayAttendance(string courseName, Student S, int courseIndex, int total)
    {
        string fileName = courseName + "_attendance.csv";

        ifstream file(fileName);
        totalStudents = total;
        int ROWS = total + 1;
        int row = 0;
        int countClasses = 0;
        int count = 0;
        bool found = false;

        string line;

        if (file.is_open())
        {
            while (getline(file, line))
            {
                if (row >= ROWS)
                {
                    break;
                }

                stringstream lineStream(line);
                string cell;

                int column = 0;
                while (getline(lineStream, cell, ','))
                {
                    if (column == 0 && row > 0)
                    {
                        if (cell == S.getName())
                        {
                            found = true;

                            // Increment missed count if attendance is 0
                            stringstream attendanceStream(line); // Reset the lineStream
                            while (getline(attendanceStream, cell, ','))
                            {
                                if (column > 0)
                                {
                                    if (stoi(cell) == 0)
                                    {
                                        count++;
                                    }
                                }
                                column++;
                            }

                            countClasses = column - 1; // Subtract 1 for the first column (student name)
                            S.setTotalClasses(countClasses, courseIndex);
                            S.setMissed(count, courseIndex);
                            break;
                        }
                    }

                    else
                    {
                        column++;
                    }
                }

                row++;

                if (found) // Check if the desired student's attendance was found
                {
                    break; // Exit the outer while loop
                }
            }
        }

        if (!found)
        {
            return;
        }

        else if (S.getTotalClasses(courseIndex) != 0)
        {
            S.setTotalClasses(countClasses, courseIndex);
            S.setAttendedClasses(courseIndex);
            S.setPercentage(courseIndex);

            totalClasses = S.getTotalClasses(courseIndex);

            cout << "\n\nCourse: " << courseName;
            cout << "\n\tTotal Classes: " << S.getTotalClasses(courseIndex);
            cout << "\n\tAttended Classes: " << S.getAttendedClasses(courseIndex);
            cout << "\n\tPercentage: " << S.getPercentage(courseIndex) << "%" << endl
                 << endl;
        }
    }

    // ~Attendance()
    // {
    //     for (int i = 0; i < totalClasses; i++)
    //     {
    //         delete[] attendedClasses[i];
    //     }
    //     delete[] attendedClasses;

    //     delete[] student;
    //     delete[] classDate;
    // }
};

// Courses Class
class Course
{
    string courseName;
    string courseCode;
    Teacher CourseTeacher;
    Student *enrolledStudents;
    int enrolledCount;
    int courseIndex;
    Attendance attendance;
    Date *D;
    int totalclasses = 0;

public:
    Course()
    {
        courseName = "";
        courseCode = "";
        CourseTeacher = Teacher();
        enrolledStudents = NULL;
        enrolledCount = 0;
        totalclasses = 0;
    }

    Course(string name, string code, Teacher t, Student *s, int count)
    {
        courseName = name;
        courseCode = code;
        CourseTeacher = t;
        enrolledCount = count;

        enrolledStudents = new Student[enrolledCount];
        for (int i = 0; i < enrolledCount; i++)
        {
            enrolledStudents[i] = s[i];
        }
    }

    Course(Course &C)
    {
        courseName = C.courseName;
        courseCode = C.courseCode;
        CourseTeacher = C.CourseTeacher;
        enrolledCount = C.enrolledCount;

        enrolledStudents = new Student[enrolledCount];
        for (int i = 0; i < enrolledCount; i++)
        {
            enrolledStudents[i] = C.enrolledStudents[i];
        }

        courseIndex = C.getCourseIndex();
        attendance = C.attendance;

        
    }

    // ~Course()
    // {
    //     delete[] enrolledStudents;
    //     enrolledStudents = NULL;
    //     delete[] D;
    //     D = NULL;
    // }

    string getCourseName()
    {
        return courseName;
    }

    string getCourseCode()
    {
        return courseCode;
    }

    Teacher getCourseTeacher()
    {
        return CourseTeacher;
    }

    Student getEnrolledStudents(int i)
    {
        return enrolledStudents[i];
    }

    int getEnrolledCount()
    {
        return enrolledCount;
    }

    int getCourseIndex()
    {
        return courseIndex;
    }

    int getTotalClasses()
    {
        return totalclasses;
    }

    void setCourseName(string name)
    {
        courseName = name;
    }

    void setCourseCode(string code)
    {
        courseCode = code;
    }

    void setCourseTeacher(Teacher t)
    {
        CourseTeacher = t;
    }

    void setEnrolledStudent(Student s, int index)
    {
        enrolledStudents[index] = s;
    }

    void setEnrolledCount(int count)
    {
        enrolledCount = count;
    }

    void setCourseIndex(int index)
    {
        courseIndex = index;
    }

    void setTotalClasses(int total)
    {
        totalclasses = total;
    }

    void setDate(Date *D)
    {
        this->D = new Date[totalclasses];
        this->D = D;
    }

    void setAttendace(int students)
    {
        attendance.setTotalStudents(students);
        attendance.setTotalCLasses(1);
        attendance.setAttendance(D, enrolledStudents);
        string fileName = courseName + "_attendance.csv";
        attendance.write(fileName);
    }

    void setNewAttendance(int students, Date myDate)
    {
        attendance.setTotalStudents(students);
        attendance.setNewAttendance(myDate, enrolledStudents);

        string fileName = courseName + "_attendance.csv";
        attendance.addAttendance(fileName, myDate);
    }

    void displayAttendance(string courseN, Student S, int courseIndex, int total)
    {
        attendance.displayAttendance(courseN, S, courseIndex, total);
    }

    void enrollStudent(int index, Student S)
    {
        // Increase the capacity of enrolledStudents if needed
        if (index >= enrolledCount)
        {
            int newCapacity = index + 1;
            Student *newStudents = new Student[newCapacity];

            // Copy existing students to the new array
            for (int i = 0; i < enrolledCount; i++)
            {
                newStudents[i] = enrolledStudents[i];
            }

            delete[] enrolledStudents;      // Deallocate the old array
            enrolledStudents = newStudents; // Update enrolledStudents pointer
            enrolledCount = newCapacity;    // Update enrolledCount
        }

        enrolledStudents[index] = S;
    }

    void removeEnrolledStudent(int index)
    {
        for (int i = index; i < enrolledCount; i++)
        {
            enrolledStudents[i] = enrolledStudents[i + 1];
        }
        enrolledCount--;
    }

    void displayEnrolledStudents()
    {
        if (enrolledStudents == NULL)
        {
            cout << "No students enrolled" << endl;
        }
        else
        {
            for (int i = 0; i < enrolledCount; i++)
            {
                cout << "\t" << i + 1 << ". ";
                enrolledStudents[i].displayStudent();
            }
        }
    }

    void display()
    {
        cout << "\nCourse Name: " << getCourseName();
        cout << "\nCourse Code: " << getCourseCode();
        cout << "\nCourse Teacher: " << CourseTeacher.getName();
        cout << "\nEnrolled Students:\n";

        displayEnrolledStudents();
    }

    friend ostream &operator<<(ostream out, Course &C);
};

ostream &operator<<(ostream &out, Course &C)
{
    out << "\nCourse Name: " << C.getCourseName();
    out << "\nCourse Code: " << C.getCourseCode();
    out << "\nCourse Teacher: " << C.getCourseTeacher().getName();
    out << "\nEnrolled Students:\n";

    for (int i = 0; i < C.getEnrolledCount(); i++)
    {
        out << "\t" << i + 1 << ". " << C.getEnrolledStudents(i).getName() << " - " << C.getEnrolledStudents(i).getRollNo() << ".\n";
    }

    return out;
}

class Time
{
    int hours;
    int minutes;
    int seconds;

public:
    Time()
    {
        hours = 0;
        minutes = 0;
        seconds = 0;
    }

    Time(int h, int m, int s)
    {
        hours = h;
        minutes = m;
        seconds = s;
    }

    int getHours()
    {
        return hours;
    }

    int getMinutes()
    {
        return minutes;
    }

    int getSeconds()
    {
        return seconds;
    }

    void setHours(int h)
    {
        hours = h;
    }

    void setMinutes(int m)
    {
        minutes = m;
    }

    void setSeconds(int s)
    {
        seconds = s;
    }

    bool isQuizAttemptable(tm *startTm, tm *endTm)
    {
        time_t currentTime = time(nullptr);
        return (currentTime >= mktime(startTm) && currentTime <= mktime(endTm));
    }

    bool calculateTime(Time start, int quizDuration)
    {
        time_t currentTimestamp = time(nullptr);
        tm *currentTm = localtime(&currentTimestamp);

        int startHour = currentTm->tm_hour;
        int startMinute = currentTm->tm_min;

        // Create a tm struct for the current date and current time as the start time
        tm quizStartTm = *currentTm;
        quizStartTm.tm_sec = 0;

        // Convert the quiz start time to a time_t timestamp
        time_t startTimestamp = mktime(&quizStartTm);

        // Calculate the quiz end time by adding the duration
        time_t endTimestamp = startTimestamp + quizDuration * 60;
        tm *endTm = localtime(&endTimestamp);
        endTm->tm_sec = 0;

        // Output quiz start and end time
        cout << "Quiz start time: " << put_time(&quizStartTm, "%H:%M") << endl;
        cout << "Quiz end time: " << put_time(endTm, "%H:%M") << endl;

        // Check if quiz is still attemptable
        bool isAttemptable = isQuizAttemptable(&quizStartTm, endTm);
        cout << "Quiz is " << (isAttemptable ? "attemptable" : "not attemptable") << endl;

        return isAttemptable;
    }
};

class Question
{
private:
    string questionType;
    string questionText;
    string option1;
    string option2;
    string option3;
    string option4;
    string answerText;
    string attemptAnswer;
    string topic;

public:
    void setQuestionType(const string &type)
    {
        questionType = type;
    }

    void setQuestionText(const string &text)
    {
        questionText = text;
    }

    void setOptions(const string &op1, const string &op2, const string &op3, const string &op4)
    {
        option1 = op1;
        option2 = op2;
        option3 = op3;
        option4 = op4;
    }

    void setAnswerText(const string &text)
    {
        answerText = text;
    }

    void setTopic(const string &topic)
    {
        this->topic = topic;
    }

    string getQuestionType() const
    {
        return questionType;
    }

    string getQuestionText() const
    {
        return questionText;
    }

    string getOption1() const
    {
        return option1;
    }

    string getOption2() const
    {
        return option2;
    }

    string getOption3() const
    {
        return option3;
    }

    string getOption4() const
    {
        return option4;
    }

    string getAnswerText() const
    {
        return answerText;
    }

    string getTopic() const
    {
        return topic;
    }

    void displayQuestion(string type) const
    {
        if (questionType == type || type == "all")
        {
            if (questionType == "b94d27b" || questionType == "2efcde9" || questionType == "88f7ace")
            {
                cout << "\t\t--------  --------\n";
                // cout << "Topic: " << topic << endl;
                cout << "Type: " << questionType << endl;
                cout << "\n"
                     << "Question:"
                     << " " << questionText << endl;

                if (questionType == "2efcde9")
                {
                    cout << "Options:"
                         << endl;
                    cout << "  A. " << option1 << endl;
                    cout << "  B. " << option2 << endl;
                    cout << "  C. " << option3 << endl;
                    cout << "  D. " << option4 << endl;
                }

                else if (questionType == "b94d27b")
                {
                    cout << "Options:"
                         << endl;
                    cout << "  A. " << option1 << endl;
                    cout << "  B. " << option2 << endl;
                }

                else if (questionType == "88f7ace")
                {
                    if (option1 != "")
                    {
                        cout << "Options:" << endl;

                        cout << "  A. " << option1 << endl;
                    }

                    if (option2 != "")
                    {
                        cout << "  B. " << option2 << endl;
                    }

                    if (option3 != "")
                    {
                        cout << "  C. " << option3 << endl;
                    }

                    if (option4 != "")
                    {
                        cout << "  D. " << option4 << endl;
                    }
                }

                cout << endl;
            }
        }
    }

    void displayAnswer()
    {
        cout << "\n"
             << "Answer:"
             << " " << answerText << endl;
    }

    Question &operator=(const Question &other)
    {
        if (this != &other)
        {
            this->questionType = other.questionType;
            this->questionText = other.questionText;
            this->option1 = other.option1;
            this->option2 = other.option2;
            this->option3 = other.option3;
            this->option4 = other.option4;
            this->answerText = other.answerText;
            this->topic = other.topic;
        }

        return *this;
    }
};

class QuestionBank
{
private:
    Question *questions;
    int questionCount;

public:
    QuestionBank()
    {
        questions = nullptr;
        questionCount = 0;
    }

    QuestionBank(QuestionBank &bank)
    {
        questionCount = bank.getQuestionCount();

        questions = new Question[questionCount];
        for (int i = 0; i < questionCount; i++)
        {
            questions[i] = bank.getQuestion(i);
        }
    }

    // ~QuestionBank()
    // {
    //     delete[] questions;
    // }

    QuestionBank getQuestionBank()
    {
        return *this;
    }

    Question getQuestion(int i)
    {
        return questions[i];
    }

    int getQuestionCount()
    {
        return questionCount;
    }

    void setQuestionCount(int count)
    {
        questionCount = count;
    }

    void readQuestionBank(string filename)
    {
        filename = "Programming Fundamentals_questionBank.txt";
        ifstream inputFile(filename);
        Question question;

        if (!inputFile.is_open())
        {
            cout << "Failed to open file: " << filename << endl;
            return;
        }

        string line;
        int currentIndex = 0;
        string topic = "";

        while (getline(inputFile, line))
        {
            if (line.empty())
            {
                continue; // Skip empty lines
            }

            if (line.length() == 7 && line == "dabfac4")
            {
                continue;
            }

            if (line.length() == 7 && line == "a5380ee")
            {
                getline(inputFile, line);
                topic = line;
                question.setTopic(topic);
                continue;
            }

            if (line.length() == 7 && (line == "2efcde9" || line == "b94d27b" || line == "88f7ace"))
            {
                question.setQuestionType(line);
            }

            getline(inputFile, line);
            question.setQuestionText(line);

            // Read options and answer
            if (question.getQuestionType() == "2efcde9")
            {
                getline(inputFile, line); // Option 1
                question.setOptions(line, "", "", "");

                getline(inputFile, line); // Option 2
                question.setOptions(question.getOption1(), line, "", "");

                getline(inputFile, line); // Option 3
                question.setOptions(question.getOption1(), question.getOption2(), line, "");
                getline(inputFile, line); // Option 4

                question.setOptions(question.getOption1(), question.getOption2(), question.getOption3(), line);
                getline(inputFile, line); // Answer

                if (question.getOption1().find("dabfac4") != string::npos)
                {
                    question.setAnswerText("A");
                    question.setOptions(question.getOption1().substr(7), question.getOption2().substr(8), question.getOption3().substr(8), question.getOption4().substr(8));
                }

                else if (question.getOption2().find("dabfac4") != string::npos)
                {
                    question.setAnswerText("B");
                    question.setOptions(question.getOption1().substr(8), question.getOption2().substr(7), question.getOption3().substr(8), question.getOption4().substr(8));
                }

                else if (question.getOption3().find("dabfac4") != string::npos)
                {
                    question.setAnswerText("C");
                    question.setOptions(question.getOption1().substr(8), question.getOption2().substr(8), question.getOption3().substr(7), question.getOption4().substr(8));
                }

                else if (question.getOption4().find("dabfac4") != string::npos)
                {
                    question.setAnswerText("D");
                    question.setOptions(question.getOption1().substr(8), question.getOption2().substr(8), question.getOption3().substr(8), question.getOption4().substr(7));
                }
            }

            else if (question.getQuestionType() == "b94d27b")
            {
                getline(inputFile, line); // Option 1
                question.setOptions(line, "", "", "");

                getline(inputFile, line); // Option 2
                question.setOptions(question.getOption1(), line, "", "");

                if (question.getOption1().find("dabfac4") != string::npos)
                {
                    question.setAnswerText("A");
                    question.setOptions(question.getOption1().substr(7), question.getOption2().substr(8), "", "");
                }

                else if (question.getOption2().find("dabfac4") != string::npos)
                {
                    question.setAnswerText("B");
                    question.setOptions(question.getOption1().substr(8), question.getOption2().substr(7), "", "");
                }
            }

            else if (question.getQuestionType() == "88f7ace")
            {
                if (getline(inputFile, line))
                {
                    question.setOptions(line, "", "", "");
                    getline(inputFile, line);
                    question.setOptions(question.getOption1(), line, "", "");
                }

                else
                {
                    question.setOptions("", "", "", "");
                }

                question.setAnswerText("        ");
            }

            // Add the question to the question bank
            addQuestion(question, currentIndex);
            currentIndex++;
        }

        for (int i = 0; i < questionCount; i++)
        {
            if (questions[i].getQuestionText() == "")
            {
                for (int j = i; j < questionCount - 1; j++)
                {
                    questions[j] = questions[j + 1];
                }

                questionCount--;
            }
        }

        inputFile.close();
    }

    void addQuestion(const Question &question, int index)
    {
        Question *newQuestions = new Question[questionCount + 1];

        for (int i = 0; i < questionCount; i++)
        {
            newQuestions[i] = questions[i];
        }

        newQuestions[questionCount] = question;

        delete[] questions;
        questions = newQuestions;

        questionCount++;
    }

    void displayQuestionBank(string type)
    {
        for (int i = 0; i < questionCount; i++)
        {
            questions[i].displayQuestion("all");
        }
    }

    void displayRandomQuestions(int total)
    {
        srand(static_cast<unsigned int>(time(0)));
        bool usedIndices[questionCount] = {false};

        for (int i = 0; i < total; i++)
        {
            int j;
            do
            {
                j = rand() % questionCount;
            } while (j == i || usedIndices[j]);

            usedIndices[j] = true;

            questions[j].displayQuestion("all");
        }
    }
};

class QuizAttempt
{
    Student *students;
    int totalMarks;
    float marksObtained;

public:
    // ~QuizAttempt()
    // {
    //     delete[] students;
    // }

    void setTotalMarks(int marks)
    {
        totalMarks = marks;
    }

    void setObtained(float marks)
    {
        marksObtained = marks;
    }

    float getMarksObtained()
    {
        return marksObtained;
    }

    int getTotalMarks()
    {
        return totalMarks;
    }
};

class Quiz
{
    string quizName;
    Date quizDate;
    Time quizTime;

    int quizDuration;
    QuestionBank questions;
    int totalQuestions;
    int attemptedQuestions;
    QuizAttempt attempt;

public:
    Quiz()
    {
        quizName = "";
        quizDate = Date();
        quizTime = Time();
        quizDuration = 0;
        totalQuestions = 0;
        attemptedQuestions = 0;
    }

    Quiz(string name, Date D, Time T, int duration, Question *q, int total)
    {
        quizName = name;
        quizDate = D;
        quizTime = T;
        quizDuration = duration;
        totalQuestions = total;
        attemptedQuestions = 0;
    }

    // Getter Methods
    string getQuizName()
    {
        return quizName;
    }

    Date getQuizDate()
    {
        return quizDate;
    }

    Time getQuizTime()
    {
        return quizTime;
    }

    int getQuizDuration()
    {
        return quizDuration;
    }

    int getTotalQuestions()
    {
        return totalQuestions;
    }

    int getAttemptedQuestion()
    {
        return attemptedQuestions;
    }

    // Setter Methods
    void setQuizName(string name)
    {
        quizName = name;
    }

    void setQuizDate(Date D)
    {
        quizDate = D;
    }

    void setQuizTime(Time T)
    {
        quizTime = T;
    }

    void setQuizDuration(int duration)
    {
        quizDuration = duration;
    }

    void setQuestionBank(const QuestionBank &bank)
    {
        questions = bank;
    }

    void setTotalQuestion(int total)
    {
        totalQuestions = total;
    }

    // void createQuiz(string fileName)
    // {
    //     fileName += ".txt";

    //     questions.displayRandomQuestions(totalQuestions);
    // }

    void createQuiz(const string &fileName)
    {
        ofstream outputFile(fileName + ".txt");

        if (!outputFile)
        {
            cout << "Failed to create the file." << endl;
            return;
        }

        // Assuming questions.displayRandomQuestions(totalQuestions) writes the output to cout
        // Replace the following line with your actual code to generate the quiz

        streambuf *coutBuf = cout.rdbuf(); // Save the original cout buffer
        cout.rdbuf(outputFile.rdbuf());    // Redirect cout to the outputFile

        questions.displayRandomQuestions(totalQuestions); // Write the output to the outputFile

        cout.rdbuf(coutBuf); // Restore the original cout buffer

        outputFile.close();

        cout << "Quiz created successfully." << endl;
    }

    void getQuiz(string fileName)
    {
        fileName = fileName + ".txt";
        ifstream inputFile(fileName);
        Question question;

        if (!inputFile.is_open())
        {
            cout << "Failed to open file: " << fileName << endl;
            return;
        }

        string line;
        int currentIndex = 0;
        string topic = "";

        while (getline(inputFile, line))
        {
            if (line.empty())
            {
                continue; // Skip empty lines
            }

            if (line == "		--------  --------")
            {
                continue;
            }

            if (line.find("Type:"))
            {
                question.setQuestionText(line.substr(10));
                getline(inputFile, line);
            }

            else if (line.find("Question:"))
            {
                question.setQuestionType(line.substr(6));
                getline(inputFile, line);
            }

            if (line.find("Options:"))
            {
                continue;
            }

            // Read options and answer
            if (question.getQuestionType() == "2efcde9")
            {
                getline(inputFile, line); // Option 1
                question.setOptions(line.substr(5), "", "", "");

                getline(inputFile, line); // Option 2
                question.setOptions(question.getOption1(), line.substr(5), "", "");

                getline(inputFile, line); // Option 3
                question.setOptions(question.getOption1(), question.getOption2(), line.substr(5), "");
                getline(inputFile, line); // Option 4

                question.setOptions(question.getOption1(), question.getOption2(), question.getOption3(), line.substr(5));
                getline(inputFile, line); // Answer

                if (question.getOption1().find("dabfac4") != string::npos)
                {
                    question.setAnswerText("A");
                    question.setOptions(question.getOption1().substr(9), question.getOption2(), question.getOption3(), question.getOption4());
                }

                else if (question.getOption2().find("dabfac4") != string::npos)
                {
                    question.setAnswerText("B");
                    question.setOptions(question.getOption1(), question.getOption2().substr(9), question.getOption3(), question.getOption4());
                }

                else if (question.getOption3().find("dabfac4") != string::npos)
                {
                    question.setAnswerText("C");
                    question.setOptions(question.getOption1(), question.getOption2(), question.getOption3().substr(9), question.getOption4());
                }

                else if (question.getOption4().find("dabfac4") != string::npos)
                {
                    question.setAnswerText("D");
                    question.setOptions(question.getOption1(), question.getOption2(), question.getOption3(), question.getOption4().substr(9));
                }
            }

            else if (question.getQuestionType() == "b94d27b")
            {
                getline(inputFile, line); // Option 1
                question.setOptions(line.substr(5), "", "", "");

                getline(inputFile, line); // Option 2
                question.setOptions(question.getOption1(), line.substr(5), "", "");

                if (question.getOption1().find("dabfac4") != string::npos)
                {
                    question.setAnswerText("A");
                    question.setOptions(question.getOption1().substr(9), question.getOption2(), question.getOption3(), question.getOption4());
                }

                else if (question.getOption2().find("dabfac4") != string::npos)
                {
                    question.setAnswerText("B");
                    question.setOptions(question.getOption1(), question.getOption2().substr(9), question.getOption3(), question.getOption4());
                }
            }

            else if (question.getQuestionType() == "88f7ace")
            {
                if (getline(inputFile, line))
                {
                    question.setOptions(line, "", "", "");
                    getline(inputFile, line);
                    question.setOptions(question.getOption1(), line, "", "");
                }

                else
                {
                    question.setOptions("", "", "", "");
                }

                question.setAnswerText("        ");
            }

            // Add the question to the question bank
            questions.addQuestion(question, currentIndex);
            currentIndex++;
        }

        inputFile.close();
    }

    void displayQuiz()
    {
        questions.displayQuestionBank("all");
    }

    void attemptQuiz()
    {
        string ans;
        if (quizTime.calculateTime(quizTime, 10))
        {
            attempt.setTotalMarks(totalQuestions);
            attempt.setObtained(0);
            setTotalQuestion(questions.getQuestionCount());

            for (int i = 0; i < totalQuestions; i++)
            {
                questions.getQuestion(i).displayQuestion("all");
                cout << "Answer: ";
                getline(cin, ans);

                if (ans == questions.getQuestion(i).getAnswerText())
                {
                    int wordCount = 0;
                    bool inWord = false;

                    for (char c : ans)
                    {

                        if (c == ' ')
                        {
                            // Start of a new word
                            inWord = true;
                            wordCount++;
                        }

                        else
                        {
                            if (!inWord)
                            {
                                // Start of a new word
                                inWord = true;
                                wordCount++;
                            }
                        }
                    }

                    if (wordCount == 1)
                    {
                        attempt.setObtained(attempt.getMarksObtained() + 1);
                    }

                    else
                    {
                        if (wordCount > 10)
                        {
                            attempt.setObtained(attempt.getMarksObtained() + 1);
                        }

                        else
                        {
                            int m;
                            m = wordCount * 0.1;
                            attempt.setObtained(attempt.getMarksObtained() + m);
                        }
                    }
                }

                else
                {
                }
            }

            cout << endl;
        }
    }

    void getQuizResult()
    {
        cout << "\nTotal Questions: " << totalQuestions;
        cout << "\nTotal Marks: " << totalQuestions;
        cout << "\nObtained Marks: " << attempt.getMarksObtained();
    }
};

class FileHandling
{
    string path;
    Course *courses;
    int totalStudents;
    int totalCourses;
    Student *S;
    Course C;
    Teacher T;

public:
    FileHandling()
    {
        path = "";
        courses = NULL;
        totalStudents = 0;
        totalCourses = 0;
        S = NULL;
        C = Course();
    }

    FileHandling(string path)
    {
        this->path = path;
        totalStudents = 217;
        totalCourses = 12;

        courses = new Course[totalCourses];
        S = new Student[totalStudents];
    }

    // ~FileHandling()
    // {
    //     delete[] courses;
    //     delete[] S;
    // }

    void read()
    {
        ifstream file(path);
        string line;
        const int ROWS = 219;
        int row = 0;
        int count[11] = {0}; // cont register in each course
        int countRegisterCourses[216] = {0};
        int studentIndex = 0; // Student index

        if (file.is_open())
        {
            while (getline(file, line))
            {
                if (row >= ROWS)
                {
                    break;
                }

                stringstream lineStream(line);
                string cell;

                int column = 0;
                int courseIndex = 0; // Initialize course index
                int enrollIndex = 0; // enroll index
                int registered[12] = {0};

                while (getline(lineStream, cell, ','))
                {
                    if (column >= 3 && row == 0)
                    {
                        courses[courseIndex].setCourseName(cell);

                        if (column == 3)
                        {
                            T.setName("Ayesha Kamran");
                            courses[courseIndex].setCourseTeacher(T);
                            courses[courseIndex].setCourseIndex(courseIndex);
                        }

                        else if (column == 4)
                        {
                            T.setName("Adil Majeed");
                            courses[courseIndex].setCourseTeacher(T);
                            courses[courseIndex].setCourseIndex(courseIndex);
                        }

                        else if (column == 5)
                        {
                            T.setName("Asim Ali");
                            courses[courseIndex].setCourseTeacher(T);
                            courses[courseIndex].setCourseIndex(courseIndex);
                        }

                        else if (column == 6)
                        {
                            T.setName("Hassan Mujtaba");
                            courses[courseIndex].setCourseTeacher(T);
                            courses[courseIndex].setCourseIndex(courseIndex);
                        }

                        else if (column == 7)
                        {
                            T.setName("Hassan Raza");
                            courses[courseIndex].setCourseTeacher(T);
                            courses[courseIndex].setCourseIndex(courseIndex);
                        }

                        else if (column == 8)
                        {
                            T.setName("Zainab Fatima");
                            courses[courseIndex].setCourseTeacher(T);
                            courses[courseIndex].setCourseIndex(courseIndex);
                        }

                        else if (column == 9)
                        {
                            T.setName("Ahmed Mujtaba");
                            courses[courseIndex].setCourseTeacher(T);
                            courses[courseIndex].setCourseIndex(courseIndex);
                        }

                        else if (column == 10)
                        {
                            T.setName("Aiman Ashraf");
                            courses[courseIndex].setCourseTeacher(T);
                            courses[courseIndex].setCourseIndex(courseIndex);
                        }

                        else if (column == 11)
                        {
                            T.setName("Naveed Aslam");
                            courses[courseIndex].setCourseTeacher(T);
                            courses[courseIndex].setCourseIndex(courseIndex);
                        }

                        else if (column == 12)
                        {
                            T.setName("Raja Allahyar");
                            courses[courseIndex].setCourseTeacher(T);
                            courses[courseIndex].setCourseIndex(courseIndex);
                        }

                        else if (column == 13)
                        {
                            T.setName("Maryam Iftikhar");
                            courses[courseIndex].setCourseTeacher(T);
                            courses[courseIndex].setCourseIndex(courseIndex);
                        }

                        courseIndex++;
                    }

                    else if (column >= 3 && row == 1)
                    {
                        courses[enrollIndex].setCourseCode(cell);
                        enrollIndex++;
                    }

                    else if (row >= 2 && row < 219)
                    {
                        if (column == 0)
                        {
                            S[studentIndex].setSerial(cell);
                        }

                        if (column == 1)
                        {
                            totalStudents++;
                            S[studentIndex].setRollNo(cell);
                        }

                        else if (column == 2)
                        {
                            S[studentIndex].setName(cell);
                            S[studentIndex].setUsername(cell);
                        }

                        else if (column >= 3)
                        {
                            if (cell[0] - 48 == 1)
                            {
                                if (S[studentIndex].getName() != "")
                                {
                                    count[enrollIndex]++;
                                    countRegisterCourses[studentIndex]++;

                                    courses[enrollIndex].enrollStudent(courses[enrollIndex].getEnrolledCount(), S[studentIndex]);
                                    courses[enrollIndex].setEnrolledCount(count[enrollIndex]);

                                    S[studentIndex].setCourseCount(countRegisterCourses[studentIndex] - 1);
                                }
                            }

                            enrollIndex++;
                        }
                    }

                    column++;
                }
                if (row >= 2)
                {
                    studentIndex++;
                }

                courseIndex++;
                row++;
            }

            // if (row == 219)
            // {
            //     if ((courses[0].getEnrolledCount() == 50) &&
            //         (courses[1].getEnrolledCount() == 38) &&
            //         (courses[2].getEnrolledCount() == 36) &&
            //         (courses[3].getEnrolledCount() == 40) &&
            //         (courses[4].getEnrolledCount() == 37) &&
            //         (courses[5].getEnrolledCount() == 53) &&
            //         (courses[6].getEnrolledCount() == 42) &&
            //         (courses[7].getEnrolledCount() == 50) &&
            //         (courses[8].getEnrolledCount() == 38) &&
            //         (courses[9].getEnrolledCount() == 38) &&
            //         (courses[10].getEnrolledCount() == 45))
            //     {
            //         cout << "\nProperly Read\n";
            //     }
            // }

            file.close(); // Close the file after reading
        }

        else
        {
            cout << "Unable to open file" << endl;
        }
    }

    Course getCourse(int i)
    {
        return courses[i];
    }

    Student getStudent(int i)
    {
        return S[i];
    }

    void update()
    {
        delete[] courses;
        courses = new Course[totalCourses];

        delete[] S;
        S = new Student[totalStudents];

        read();
    }

    void getRegistredCourses(Student S)
    {
        cout << "\nRegistered Courses:\n";
        for (int i = 0; i < 11; i++)
        {
            for (int j = 0; j < courses[i].getEnrolledCount(); j++)
            {
                Student temp = courses[i].getEnrolledStudents(j);
                if (temp == S)
                {
                    cout << "\t" << courses[i].getCourseCode() << " - " << courses[i].getCourseName() << endl;
                }
            }
        }
    }

    bool registerCourse(int index, Student &Stu)
    {
        const int ROWS = 219;
        int row = 0;
        int myRow = Stu.getSerial() + 3;
        int myCol = index + 2;

        ifstream inputFile(path);      // Open input CSV file
        ofstream tempFile("temp.csv"); // Create temporary file for writing

        string line;
        while (getline(inputFile, line))
        {
            istringstream iss(line);
            string cell;
            int column = 0;
            string modifiedLine;

            while (getline(iss, cell, ','))
            {
                if (row == myRow && column == myCol)
                {
                    // Modify the desired cell value
                    cell = "1";
                }

                modifiedLine += cell + ",";
                column++;
            }

            // Remove trailing comma
            modifiedLine.pop_back();

            // Write the modified line to the temporary file
            tempFile << modifiedLine << endl;

            row++;
        }

        inputFile.close();
        tempFile.close();
        // Delete the original file
        remove(path.c_str());

        // Rename the temporary file to the original file name
        rename("temp.csv", path.c_str());

        return true;
    }

    bool dropCourse(int index, Student &Stu)
    {
        const int ROWS = 219;
        int row = 0;
        int myRow = Stu.getSerial() + 3;
        int myCol = index + 2;

        ifstream inputFile(path);      // Open input CSV file
        ofstream tempFile("temp.csv"); // Create temporary file for writing

        string line;
        while (getline(inputFile, line))
        {
            istringstream iss(line);
            string cell;
            int column = 0;
            string modifiedLine;

            while (getline(iss, cell, ','))
            {
                if (row == myRow && column == myCol)
                {
                    // Modify the desired cell value
                    cell = "0";
                }

                modifiedLine += cell + ",";
                column++;
            }

            // Remove trailing comma
            modifiedLine.pop_back();

            // Write the modified line to the temporary file
            tempFile << modifiedLine << endl;

            row++;
        }

        inputFile.close();
        tempFile.close();
        // Delete the original file
        remove(path.c_str());

        // Rename the temporary file to the original file name
        rename("temp.csv", path.c_str());

        return true;
    }

    void display(int index)
    {
        courses[index].display();
    }
};

int main()
{
    FileHandling file("Course Registration Data.csv");

    file.read();

    Course *courses;
    courses = new Course[11];

    Student *students;
    students = new Student[217];

    Teacher *teachers;
    teachers = new Teacher[11];

    for (int i = 0; i < 11; i++)
    {
        courses[i] = file.getCourse(i);
    }

    for (int i = 0; i < 217; i++)
    {
        students[i] = file.getStudent(i);
    }

    for (int i = 0; i < 11; i++)
    {
        teachers[i] = courses[i].getCourseTeacher();
        teachers[i].setUsername(teachers[i].getName());
    }

    Student student;
    Teacher teacher;
    Attendance attendance;
    string username, password, name;

    bool login = false, regist = false;
    char choice, again, studentChoice;
    char quit;
    int loginChoice, loginAs;
    int studentIndex = 0, teacherIndex = 0;
    int loggedIn;
    string studentDrop;

    int courseRegister = 0, drop = 0;
    Student loggedInStudent, temp;
    Teacher loggedInTeacher;

    Date *D;
    D = new Date[1];

    int date, month, year, hours, minutes, seconds, totalQs;
    string quizName;

    QuestionBank *bank;
    bank = new QuestionBank[11];

    Quiz *quiz;
    quiz = new Quiz[11];

    QuizAttempt attempt;
    int i, k = 0;

    system("cls");
    do
    {
        cout << "\n\t---------------------- Menu ----------------------\n";
        cout << "\n\n1. Login";
        cout << "\n2. Register";
        cout << "\n3. Quit";
        cout << "\nChoice: ";
        cin >> loginChoice;

        system("cls");
        switch (loginChoice)
        {
        case 1:
            cout << "\n\t---------------------- Login As ----------------------\n";

            cout << "\n\n1.Student";
            cout << "\n2.Teacher\n";
            cout << "Choice: ";
            cin >> loginAs;

            system("cls");

            switch (loginAs)
            {
            case 1:
                cout << "\n\t---------------------- Login ----------------------\n";
                cout << "\n\nEnter Username: ";
                cin >> username;

                cout << "\nEnter Password: ";
                cin >> password;

                student.setUsername(username);
                student.setPassword(password);
                student.setName(name);

                login = student.loginStudent();

                do
                {
                    if (login)
                    {
                        cout << "\n\nSuccessful Login!\n\n";
                        for (int j = 0; j < 217; j++)
                        {
                            if ((students[j].getUsername()) == (student.getUsername()))
                            {
                                studentIndex = j;
                                break;
                            }
                        }

                        loggedInStudent = students[studentIndex];
                        loggedIn = 1;
                    }

                    else
                    {
                        cout << "\nLogin Failed!\n\nTry Again!\n\n";
                        system("pause");
                        system("cls");

                        cout << "\n\t---------------------- Login ----------------------\n";
                        cout << "\nEnter Username: ";
                        cin >> username;

                        cout << "\nEnter Password: ";
                        cin >> password;

                        student.setUsername(username);
                        student.setPassword(password);
                        student.setName(name);

                        login = student.loginStudent();
                    }
                } while (login != true);

                break;

            case 2:
                cout << "\n\t---------------------- Login ----------------------\n";
                cout << "\n\nEnter Username: ";
                cin >> username;
                cout << "\nEnter Password: ";
                cin >> password;

                teacher.setUsername(username);
                teacher.setPassword(password);
                login = teacher.loginTeacher();

                do
                {
                    if (login)
                    {
                        cout << "\n\nSuccessful Login!\n\n";
                        for (int j = 0; j < 11; j++)
                        {
                            if ((teachers[j].getUsername()) == (teacher.getUsername()))
                            {
                                teacherIndex = j;
                                break;
                            }
                        }

                        loggedIn = 2;
                        loggedInTeacher = teachers[teacherIndex];
                    }

                    else
                    {
                        cout << "\nLogin Failed!\nTry Again!\n\n";
                        system("pause");
                        system("cls");

                        cout << "\n\t---------------------- Login ----------------------\n";
                        cout << "\n\nEnter Username: ";
                        cin >> username;
                        cout << "\nEnter Password: ";
                        cin >> password;

                        teacher.setUsername(username);
                        teacher.setPassword(password);
                        login = teacher.loginTeacher();
                    }
                } while (login != true);

                break;

            default:
                break;
            }

            system("cls");

            if (loginAs == 1)
            {
                do
                {
                    cout << "\n\t---------------------- Menu ----------------------\n";

                    cout << "\n\n\tA. Display Registered Courses.";
                    cout << "\n\tB. Register New Course";
                    cout << "\n\tC. Drop a Course";
                    cout << "\n\tD. Display Attendance";
                    cout << "\n\tE. Attempt Quiz";
                    cout << "\n\tF. Display Result of Quiz";
                    cout << "\n\tG. Display Analytics Report";
                    cout << "\n\tH. Logout";
                    cout << "\n\tI. Quit";
                    cout << "\n\nChoice: ";
                    cin >> choice;

                    system("cls");

                    switch (tolower(choice))
                    {
                    case 'a':

                        file.getRegistredCourses(loggedInStudent);
                        cout << "\n\n";
                        system("pause");
                        break;

                    case 'b':
                        cout << "\n\nWhich course do you want to register:\n";
                        for (int i = 0; i < 11; i++)
                        {
                            cout << "\n\t" << i + 1 << ". " << courses[i].getCourseCode() << " " << courses[i].getCourseName();
                        }
                        cout << "\n\nChoice (Course Number (1-11)): ";
                        cin >> courseRegister;

                        file.registerCourse(courseRegister, loggedInStudent);
                        file.update();

                        delete[] courses;
                        courses = new Course[11];

                        delete[] students;
                        students = new Student[217];

                        system("cls");

                        for (int i = 0; i < 11; i++)
                        {
                            courses[i] = file.getCourse(i);
                        }

                        for (int i = 0; i < 217; i++)
                        {
                            students[i] = file.getStudent(i);
                        }

                        file.getRegistredCourses(loggedInStudent);

                        system("pause");
                        break;

                    case 'c':
                        cout << "\n\nWhich course do you want to drop:\n";
                        file.getRegistredCourses(loggedInStudent);

                        cout << "\n\nChoice (Course Code - Upper Case): ";
                        cin.ignore();
                        getline(cin, studentDrop);

                        for (int i = 0; i < 11; i++)
                        {
                            if (studentDrop == courses[i].getCourseCode())
                            {
                                cout << courses[i].getCourseIndex();
                                courseRegister = courses[i].getCourseIndex();
                            }
                        }

                        file.dropCourse(courseRegister, loggedInStudent);
                        file.update();

                        delete[] courses;
                        courses = new Course[11];

                        delete[] students;
                        students = new Student[217];

                        system("cls");

                        for (int i = 0; i < 11; i++)
                        {
                            courses[i] = file.getCourse(i);
                        }

                        for (int i = 0; i < 217; i++)
                        {
                            students[i] = file.getStudent(i);
                        }

                        file.getRegistredCourses(loggedInStudent);

                        system("pause");
                        break;

                    case 'd':
                        for (int i = 0; i < 11; i++)
                        {
                            courses[i].displayAttendance(courses[i].getCourseName(), loggedInStudent, i, courses[i].getEnrolledCount());
                        }

                        system("pause");
                        break;

                    case 'e':
                        cout << "Enter quiz name: ";
                        cin.ignore();
                        getline(cin, quizName);

                        quiz->getQuiz(quizName);
                        totalQs = quiz->getTotalQuestions();

                        attempt.setTotalMarks(totalQs);
                        quiz->setQuizTime(Time(18, 45, 0));
                        quiz->attemptQuiz();

                        system("pause");
                        break;

                    case 'f':
                        quiz->getQuizResult();
                        cout << endl;
                        system("pause");
                        break;

                    case 'h':
                        loggedInStudent.logout();
                        studentChoice = 'q';
                        break;
                    case 'i':
                        return 0;
                    }
                } while (studentChoice != 'Q' && studentChoice != 'q');
            }

            else if (loginAs == 2)
            {

                do
                {
                    cout << "\n\t---------------------- Menu ----------------------\n";

                    cout << "\n\n\tA. Display Registered Students.";
                    cout << "\n\tB. Create Attendance";
                    cout << "\n\tC. Add new Attendance";
                    cout << "\n\tD. Display Question Bank";
                    cout << "\n\tE. Create Quiz";
                    cout << "\n\tF. Display Quiz";
                    cout << "\n\tG. Logout";
                    cout << "\n\tH. Quit";
                    cout << "\n\nChoice: ";
                    cin >> choice;

                    system("cls");

                    switch (tolower(choice))
                    {
                    case 'a':
                        courses[teacherIndex].display();
                        // courses[teacherIndex].displayEnrolledStudents();
                        system("pause");
                        break;

                    case 'b':
                        courses[teacherIndex].setTotalClasses(1);
                        cout << "\nEnter date of first class:\nDay: ";
                        cin >> date;

                        cout << "Month: ";
                        cin >> month;

                        cout << "Year: ";
                        cin >> year;

                        D[0] = Date(date, month, year);

                        courses[teacherIndex].setDate(D);
                        courses[teacherIndex].setAttendace(courses[teacherIndex].getEnrolledCount());

                        system("pause");
                        break;

                    case 'c':
                        cout << "\nEnter date of class:\nDay: ";
                        cin >> date;

                        cout << "Month: ";
                        cin >> month;

                        cout << "Year: ";
                        cin >> year;

                        D[1] = Date(date, month, year);
                        courses[teacherIndex].setNewAttendance(courses[teacherIndex].getEnrolledCount(), D[1]);

                        system("pause");

                    case 'd':
                        bank[teacherIndex].readQuestionBank(courses[teacherIndex].getCourseName());
                        bank[teacherIndex].displayQuestionBank("all");
                        system("pause");
                        break;

                    case 'e':
                        bank[teacherIndex].readQuestionBank(courses[teacherIndex].getCourseName());
                        cout << "\nEnter name of Quiz: ";
                        cin.ignore();
                        getline(cin, quizName);

                        cout << "\nSet Total Number of questions in Quiz: ";
                        cin >> totalQs;

                        quiz->setQuizName(quizName);
                        quiz->setTotalQuestion(totalQs);

                        quiz->setQuestionBank(bank[teacherIndex].getQuestionBank());
                        quiz->createQuiz(quizName);

                        system("pause");
                        break;

                    case 'f':
                        cout << "\nEnter name of Quiz: ";
                        cin.ignore();
                        getline(cin, quizName);

                        quiz->getQuiz(quizName);
                        quiz->displayQuiz();

                        system("pause");
                        break;

                    case 'g':
                        loggedInTeacher.logout();
                        studentChoice = 'q';
                        break;
                    case 'h':
                        return 0;
                    }
                } while (studentChoice != 'Q' && studentChoice != 'q');
            }
            break;

        case 2:
            cout << "\n\t---------------------- Registration As ----------------------\n";

            cout << "\n\n1.Student";
            cout << "\n2.Teacher\n";
            cout << "Choice: ";
            cin >> loginAs;

            system("cls");
            switch (loginAs)
            {
            case 1:
                cout << "\n\t---------------------- Registration ----------------------\n";
                cout << "\n\nEnter Username: ";
                cin >> username;
                cout << "\nEnter Password: ";
                cin >> password;

                student.setUsername(username);
                student.setPassword(password);
                regist = student.registerStudent();
                break;

            case 2:
                cout << "\n\t---------------------- Registration ----------------------\n";
                cout << "\n\nEnter Username: ";
                cin >> username;
                cout << "\nEnter Password: ";
                cin >> password;

                teacher.setUsername(username);
                teacher.setPassword(password);
                regist = teacher.registerTeacher();
                break;

            default:
                break;
            }

            if (regist)
            {
                cout << "\n\nSuccessful Registration!\n\n";
            }

            else
            {
                cout << "\n\nRegistration Failed!\n\n";
            }

            system("pause");
            break;

        case 3:
            quit = 'q';
        default:
            break;
        }

        system("cls");
    } while (quit != 'Q' && quit != 'q');

    return 0;
}