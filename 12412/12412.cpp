
// @snippet<sh19910711/contest:headers.cpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <limits>
#include <complex>
#include <functional>
#include <iterator>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

// @snippet<sh19910711/contest:solution/interface.cpp>
namespace solution {
    class ISolution {
    public:
        virtual void init() {};
        virtual bool input() { return false; };
        virtual void output() {};
        virtual int run() = 0;
    };
}

// @snippet<sh19910711/contest:solution/typedef.cpp>
namespace solution {
    typedef std::istringstream ISS;
    typedef std::ostringstream OSS;
    typedef std::vector<std::string> VS;
    typedef long long LL;
    typedef int INT;
    typedef std::vector<INT> VI;
    typedef std::vector<VI> VVI;
    typedef std::pair<INT,INT> II;
    typedef std::vector<II> VII;
}

namespace solution {
    using namespace std;

    typedef set<string> SID_SET;

    const int SUBJECTS = 4;
    const int MAX_STUDENTS = 111;
    enum ADD_STUDENT_RESULT {
        SUCCESS, DUPLICATED
    };
    const string SUBJECT_LABELS[SUBJECTS] = {
        "Chinese",
        "Mathematics",
        "English",
        "Programming"
    };

    string getline() {
        string res;
        getline(cin, res);
        return res;
    }

    int get_number() {
        ISS iss(getline());
        int res;
        iss >> res;
        return res;
    }

    string to_string( double x ) {
        OSS oss;
        oss << setiosflags(ios::fixed) << setprecision(20) << abs(x);
        string s = oss.str();
        int n = s.size();
        for ( int i = 0; i < n; ++ i )
            if ( s[i] == '.' )
                return s.substr(0, i + 3);
        return "";
    }

    class StudentInfo {
    public:
        string sid;
        string cid;
        string name;
        int scores[SUBJECTS];

        StudentInfo(){}

        StudentInfo( string sid, string cid, string name, int scores[SUBJECTS] ) {
            this->sid = sid;
            this->cid = cid;
            this->name = name;
            for ( int i = 0; i < SUBJECTS; ++ i )
                this->scores[i] = scores[i];
        }

        int getSum() const {
            return accumulate(scores, scores+SUBJECTS, 0);
        }

        double getAverage() const {
            return (double)getSum() / SUBJECTS;
        }

        friend ostream& operator <<( ostream& os, const StudentInfo& si ) {
            os << si.sid << " " << si.cid << " " << si.name << " ";
            for ( int i = 0; i < SUBJECTS; ++ i )
                os << si.scores[i] << " ";
            os << si.getSum() << " ";
            os << to_string(si.getAverage());
            return os;
        }

    };

    class SPMS {
    public:
        StudentInfo si_list[MAX_STUDENTS];
        int si_cnt;
        SID_SET sid_set;
        int ranks[MAX_STUDENTS];

        SPMS() {
            si_cnt = 0;
            sid_set.clear();
        }

        void calcRanks() {
            II list[MAX_STUDENTS];
            for ( int i = 0; i < si_cnt; ++ i )
                list[i] = II(si_list[i].getSum(), i);
            sort(list, list+si_cnt, greater<II>());
            for ( int i = 0; i < si_cnt; ++ i ) {
                if ( i > 0 && list[i].first == list[i - 1].first )
                    ranks[list[i].second] = ranks[list[i - 1].second];
                else
                    ranks[list[i].second] = i + 1;
            }
        }

        ADD_STUDENT_RESULT addStudent( string sid, string cid, string name, int scores[SUBJECTS] ) {
            if ( sid_set.count(sid) )
                return DUPLICATED;
            sid_set.insert(sid);
            si_list[si_cnt ++] = StudentInfo(sid, cid, name, scores);
            calcRanks();
            return SUCCESS;
        }

        bool addStudents() {
            cout << "Please enter the SID, CID, name and four scores. Enter 0 to finish." << endl;
            string s = getline();
            if ( s == "0" )
                return false;

            ISS iss(s);
            string sid, cid, name;
            int scores[SUBJECTS];
            iss >> sid >> cid >> name;
            for ( int i = 0; i < 4; ++ i ) {
                iss >> scores[i];
            }

            if ( addStudent(sid, cid, name, scores) == DUPLICATED )
                cout << "Duplicated SID." << endl;
            return true;
        }

        void deleteStudent( int k ) {
            for ( int i = k; i + 1 < si_cnt; ++ i )
                si_list[i] = si_list[i+1];
            si_cnt --;
            calcRanks();
        }

        bool deleteStudents() {
            cout << "Please enter SID or name. Enter 0 to finish." << endl;
            string s = getline();
            if ( s == "0" )
                return false;

            ISS iss(s);
            string query;
            iss >> query;
            
            int deleted = 0;
            bool targets[MAX_STUDENTS];
            fill(targets, targets + MAX_STUDENTS, false);
            
            for ( int i = 0; i < si_cnt; ++ i ) {
                string sid;
                if ( si_list[i].sid == query ) {
                    sid = query;
                    targets[i] = true;
                }
                if ( si_list[i].name == query ) {
                    sid = si_list[i].sid;
                    targets[i] = true;
                }
                if ( ! sid.empty() )
                    sid_set.erase(sid);
            }

            for ( int i = si_cnt - 1; i >= 0; -- i ) {
                if ( targets[i] ) {
                    deleteStudent(i);
                    deleted ++;
                }
            }
            cout << deleted << " student(s) removed." << endl;

            return true;
        }

        void queryStudent( int k ) {
            StudentInfo& s = si_list[k];
            cout << ranks[k] << " " << s << endl;
        }

        bool queryStudents() {
            cout << "Please enter SID or name. Enter 0 to finish." << endl;
            string s = getline();
            if ( s == "0" )
                return false;

            ISS iss(s);
            string query;
            iss >> query;

            for ( int i = 0; i < si_cnt; ++ i ) {
                if ( si_list[i].sid == query || si_list[i].name == query ) {
                    queryStudent(i);
                }
            }

            return true;
        }

        void calcWholeClassStatistics() {
            LL sum[SUBJECTS];
            double avg[SUBJECTS];
            int students;
            int passed[SUBJECTS];
            int failed[SUBJECTS];
            fill(sum, sum + SUBJECTS, 0);
            fill(passed, passed + SUBJECTS, 0);
            fill(failed, failed + SUBJECTS, 0);
            
            for ( int i = 0; i < si_cnt; ++ i ) {
                StudentInfo& s = si_list[i];
                students += 1;
                for ( int j = 0; j < SUBJECTS; ++ j ) {
                    int score = s.scores[j];
                    sum[j] += score;
                    if ( score >= 60 )
                        passed[j] ++;
                    else
                        failed[j] ++;
                }
            }
            for ( int i = 0; i < SUBJECTS; ++ i ) {
                if ( students == 0 )
                    avg[i] = 0;
                else 
                    avg[i] = (double)sum[i] / students;
            }

            for ( int i = 0; i < SUBJECTS; ++ i ) {
                cout << SUBJECT_LABELS[i] << endl;
                cout << "Average Score: " << to_string(avg[i]) << endl;
                cout << "Number of passed students: " << passed[i] << endl;
                cout << "Number of failed students: " << failed[i] << endl;
                cout << endl;
            }

            const int OVERALL_TYPES = 5;
            int num[OVERALL_TYPES];
            fill(num, num + OVERALL_TYPES, 0);
            for ( int i = 0; i < si_cnt; ++ i ) {
                StudentInfo& s = si_list[i];
                int passed_subjects = 0;
                for ( int j = 0; j < SUBJECTS; ++ j ) {
                    if ( s.scores[j] >= 60 )
                        passed_subjects ++;
                }
                if ( passed_subjects == 0 )
                    num[0] ++;
                for ( int j = 1; j <= passed_subjects; ++ j )
                    num[j] ++;
            }
            cout << "Overall:" << endl;
            cout << "Number of students who passed all subjects: " << num[4] << endl;
            cout << "Number of students who passed 3 or more subjects: " << num[3] << endl;
            cout << "Number of students who passed 2 or more subjects: " << num[2] << endl;
            cout << "Number of students who passed 1 or more subjects: " << num[1] << endl;
            cout << "Number of students who failed all subjects: " << num[0] << endl;
            cout << endl;
        }

        void calcClassStatistics( string cid ) {
            LL sum[SUBJECTS];
            double avg[SUBJECTS];
            int students;
            int passed[SUBJECTS];
            int failed[SUBJECTS];
            fill(sum, sum + SUBJECTS, 0);
            fill(passed, passed + SUBJECTS, 0);
            fill(failed, failed + SUBJECTS, 0);
            
            for ( int i = 0; i < si_cnt; ++ i ) {
                StudentInfo& s = si_list[i];
                if ( s.cid == cid ) {
                    students += 1;
                    for ( int j = 0; j < SUBJECTS; ++ j ) {
                        int score = s.scores[j];
                        sum[j] += score;
                        if ( score >= 60 )
                            passed[j] ++;
                        else
                            failed[j] ++;
                    }
                }
            }
            for ( int i = 0; i < SUBJECTS; ++ i ) {
                if ( students == 0 )
                    avg[i] = 0;
                else 
                    avg[i] = (double)sum[i] / students;
            }

            for ( int i = 0; i < SUBJECTS; ++ i ) {
                cout << SUBJECT_LABELS[i] << endl;
                cout << "Average Score: " << to_string(avg[i]) << endl;
                cout << "Number of passed students: " << passed[i] << endl;
                cout << "Number of failed students: " << failed[i] << endl;
                cout << endl;
            }

            const int OVERALL_TYPES = 5;
            int num[OVERALL_TYPES];
            fill(num, num + OVERALL_TYPES, 0);
            for ( int i = 0; i < si_cnt; ++ i ) {
                StudentInfo& s = si_list[i];
                if ( s.cid == cid ) {
                    int passed_subjects = 0;
                    for ( int j = 0; j < SUBJECTS; ++ j ) {
                        if ( s.scores[j] >= 60 )
                            passed_subjects ++;
                    }
                    if ( passed_subjects == 0 )
                        num[0] ++;
                    for ( int j = 1; j <= passed_subjects; ++ j )
                        num[j] ++;
                }
            }
            cout << "Overall:" << endl;
            cout << "Number of students who passed all subjects: " << num[4] << endl;
            cout << "Number of students who passed 3 or more subjects: " << num[3] << endl;
            cout << "Number of students who passed 2 or more subjects: " << num[2] << endl;
            cout << "Number of students who passed 1 or more subjects: " << num[1] << endl;
            cout << "Number of students who failed all subjects: " << num[0] << endl;
            cout << endl;
        }

        void showStatistics() {
            cout << "Please enter class ID, 0 for the whole statistics." << endl;
            string s = getline();
            if ( s == "0" ) {
                calcWholeClassStatistics();
                return;
            }

            ISS iss(s);
            string query;
            iss >> query;

            calcClassStatistics(query);
            return;
        }

        bool showMenu() {
            cout << "Welcome to Student Performance Management System (SPMS)." << endl;
            cout << endl;
            cout << "1 - Add" << endl;
            cout << "2 - Remove" << endl;
            cout << "3 - Query" << endl;
            cout << "4 - Show ranking" << endl;
            cout << "5 - Show Statistics" << endl;
            cout << "0 - Exit" << endl;
            cout << endl;
            int n = get_number();
            switch ( n ) {
                case 1:
                    while ( addStudents() );
                    break;
                case 2:
                    while ( deleteStudents() );
                    break;
                case 3:
                    while ( queryStudents() );
                    break;
                case 4:
                    cout << "Showing the ranklist hurts students' self-esteem. Don't do that." << endl;
                    break;
                case 5:
                    showStatistics();
                    break;
                case 0:
                    return false;
            }
            return true;
        }

    };
    
    class Solution: public ISolution {
    public:
        
        void solve() {
            SPMS s;
            while ( s.showMenu() );
        }
        
        int run() {
            init();
            input();
            solve();
            output();
            return 0;
        }
        
    };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
    return solution::Solution().run();
}

