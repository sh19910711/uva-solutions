
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
    const int MAX_STUDENTS = 10011;
    const double EPS = 0.00001;
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
        cin >> res;
        return res;
    }

    int get_number() {
        int res;
        cin >> res;
        return res;
    }

    string to_string( double x ) {
        char buf[256];
        sprintf(buf, "%.2lf", x);
        return string(buf);
    }

    class StudentInfo {
    public:
        string sid;
        int cid;
        string name;
        int scores[SUBJECTS];

        StudentInfo(){}

        StudentInfo( string sid, int cid, string name, int scores[SUBJECTS] ) {
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
            return (double)getSum() / (double)SUBJECTS + EPS;
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
            sort(list, list + si_cnt, greater<II>());
            for ( int i = 0; i < si_cnt; ++ i ) {
                if ( i > 0 && list[i].first == list[i - 1].first )
                    ranks[list[i].second] = ranks[list[i - 1].second];
                else
                    ranks[list[i].second] = i + 1;
            }
        }

        ADD_STUDENT_RESULT addStudent( string sid, int cid, string name, int scores[SUBJECTS] ) {
            if ( sid_set.count(sid) )
                return DUPLICATED;
            sid_set.insert(sid);
            si_list[si_cnt ++] = StudentInfo(sid, cid, name, scores);
            calcRanks();
            return SUCCESS;
        }

        bool addStudents() {
            cout << "Please enter the SID, CID, name and four scores. Enter 0 to finish." << "\n";

            string sid, name;
            int cid;
            int scores[SUBJECTS];
            cin >> sid;
            if ( sid == "0" )
                return false;
            cin >> cid >> name;
            for ( int i = 0; i < 4; ++ i ) {
                cin >> scores[i];
            }

            if ( addStudent(sid, cid, name, scores) == DUPLICATED )
                cout << "Duplicated SID." << "\n";
            return true;
        }

        void deleteStudent( int k ) {
            for ( int i = k; i + 1 < si_cnt; ++ i )
                si_list[i] = si_list[i+1];
            si_cnt -= 1;
            calcRanks();
        }

        bool deleteStudents() {
            cout << "Please enter SID or name. Enter 0 to finish." << "\n";
            string query;
            cin >> query;
            if ( query == "0" )
                return false;

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
            cout << deleted << " student(s) removed." << "\n";

            return true;
        }

        void queryStudent( int k ) {
            StudentInfo& s = si_list[k];
            cout << ranks[k] << " " << s << "\n";
        }

        bool queryStudents() {
            cout << "Please enter SID or name. Enter 0 to finish." << "\n";
            string query;
            cin >> query;
            if ( query == "0" )
                return false;

            for ( int i = 0; i < si_cnt; ++ i ) {
                if ( si_list[i].sid == query || si_list[i].name == query ) {
                    queryStudent(i);
                }
            }

            return true;
        }

        void calcWholeClassStatistics() {
            int sum[SUBJECTS];
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
                    avg[i] = EPS;
                else 
                    avg[i] = (double)sum[i] / (double)students + EPS;
            }

            for ( int i = 0; i < SUBJECTS; ++ i ) {
                cout << SUBJECT_LABELS[i] << "\n";
                cout << "Average Score: " << to_string(avg[i]) << "\n";
                cout << "Number of passed students: " << passed[i] << "\n";
                cout << "Number of failed students: " << failed[i] << "\n";
                cout << "\n";
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
            cout << "Overall:" << "\n";
            cout << "Number of students who passed all subjects: " << num[4] << "\n";
            cout << "Number of students who passed 3 or more subjects: " << num[3] << "\n";
            cout << "Number of students who passed 2 or more subjects: " << num[2] << "\n";
            cout << "Number of students who passed 1 or more subjects: " << num[1] << "\n";
            cout << "Number of students who failed all subjects: " << num[0] << "\n";
            cout << "\n";
        }

        void calcClassStatistics( int cid ) {
            int sum[SUBJECTS];
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
                    avg[i] = EPS;
                else 
                    avg[i] = (double)sum[i] / (double)students + EPS;
            }

            for ( int i = 0; i < SUBJECTS; ++ i ) {
                cout << SUBJECT_LABELS[i] << "\n";
                cout << "Average Score: " << to_string(avg[i]) << "\n";
                cout << "Number of passed students: " << passed[i] << "\n";
                cout << "Number of failed students: " << failed[i] << "\n";
                cout << "\n";
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
            cout << "Overall:" << "\n";
            cout << "Number of students who passed all subjects: " << num[4] << "\n";
            cout << "Number of students who passed 3 or more subjects: " << num[3] << "\n";
            cout << "Number of students who passed 2 or more subjects: " << num[2] << "\n";
            cout << "Number of students who passed 1 or more subjects: " << num[1] << "\n";
            cout << "Number of students who failed all subjects: " << num[0] << "\n";
            cout << "\n";
        }

        void showStatistics() {
            cout << "Please enter class ID, 0 for the whole statistics." << "\n";

            int query;
            cin >> query;

            if ( query == 0 ) {
                calcWholeClassStatistics();
            } else {
                calcClassStatistics(query);
            }
        }

        bool showMenu() {
            cout << "Welcome to Student Performance Management System (SPMS)." << "\n";
            cout << "\n";
            cout << "1 - Add" << "\n";
            cout << "2 - Remove" << "\n";
            cout << "3 - Query" << "\n";
            cout << "4 - Show ranking" << "\n";
            cout << "5 - Show Statistics" << "\n";
            cout << "0 - Exit" << "\n";
            cout << "\n";
            int n;
            cin >> n;
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
                    cout << "Showing the ranklist hurts students' self-esteem. Don't do that." << "\n";
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
            solve();
            return 0;
        }
        
    };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
    return solution::Solution().run();
}

