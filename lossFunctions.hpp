//
// Created by askar on 03.04.2025.
//
#pragma once
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"

mt19937 rng(546411);

constexpr double e = 2.71828;


struct dule {
    int pars;
    int maxWorkDays;
    int maxSatDays;
    vector<vector<vector<vector<int>>>> s;//для каждой параллели, для каждого класса, для каждого дня уроки в порядке их реального следования
    vector<vector<vector<int>>> teachForClas;//для каждого урока у класса его учитель
    vector<int> subj; //для каждого учителя его урок
    vector<vector<int>> teach; //для каждого урока список учителей, преподающие этот урок
    map<string, int> toSubj; //перевод урока в номер
    vector<string> backToSubj; //обратно
    map<string, int> toTeach; //перевод учителя в номер
    vector<string> backToTeach; // обратно

    dule(int n, int k, int q, vector<string> sub, vector<string> t, vector<int> l, vector<vector<vector<int>>> a, int mxW, int mxS) {
        pars = n;
        s.resize(pars);
        maxWorkDays = mxW;
        maxSatDays = mxS;

        teachForClas.resize(pars);
        subj.resize(q);
        teach.resize(k);
        backToSubj.resize(k);
        backToTeach.resize(q);
        for (int i = 0; i < k; i++) {
            backToSubj[i] = sub[i];
            toSubj[sub[i]] = i;
        }
        for (int i = 0; i < q; i++) {
            backToTeach[i] = t[i];
            toTeach[t[i]] = i;
        }
        for (int i = 0; i < q; i++) {
            subj[i] = l[i];
            teach[l[i]].push_back(i);
        }

        for (int par = 0; par < a.size(); par++) {
            s[par].resize(a[par].size());
            teachForClas[par].resize(a[par].size());
            for (int clas = 0; clas < a[par].size(); clas++) {
                int day = 1;
                int lesson = 1;
                s[par][clas].resize(6);
                teachForClas[par][clas].resize(k);
                for (int u = 0; u < 5; u++) {
                    s[par][clas][u].resize(maxWorkDays, -1);
                }
                s[par][clas][5].resize(maxSatDays, -1);
                for (int les = 0; les < k; les++) {
                    for (int i = 0; i < a[par][clas][les]; i++) {
                        if (lesson == maxWorkDays + 1) {
                            day++;
                            lesson = 1;
                        }
                        s[par][clas][day - 1][lesson - 1] = les;
                        teachForClas[par][clas][les] = teach[les][abs((int)rng()) % teach[les].size()];
                        lesson++;
                    }
                }
            }
        }
    }

    int Pers() {
        int ans = 0;
        for (int day = 0; day < 5; day++) {
            for (int les = 0; les < maxWorkDays; les++) {
                map<int, int> cnt;
                for (int par = 0; par < s.size(); par++) {
                    for (int clas = 0; clas < s[par].size(); clas++) {
                        if (s[par][clas][day][les] == -1) continue;
                        ans += cnt[teachForClas[par][clas][s[par][clas][day][les]]] * 1e9;
                        cnt[teachForClas[par][clas][s[par][clas][day][les]]]++;
                    }
                }
            }
        }
        int day = 5;
        for (int les = 0; les < maxSatDays; les++) {
            map<int, int> cnt;
            for (int par = 0; par < s.size(); par++) {
                for (int clas = 0; clas < s[par].size(); clas++) {
                    if (s[par][clas][day][les] == -1) continue;
                    ans += cnt[teachForClas[par][clas][s[par][clas][day][les]]] * 1e9;
                    cnt[teachForClas[par][clas][s[par][clas][day][les]]]++;
                }
            }
        }
        return ans;
    }

    int comfort() {
        int ans = 0;
        for (int par = 0; par < pars; par++) {
            for (int clas = 0; clas < s[par].size(); clas++) {
                for (int day = 0; day < 6; day++) {
                    for (int t = 0; t < backToTeach.size(); t++) {
                        int l = 0, r = 0;
                        int cnt = 0;
                        for (int les = 0; les < s[par][clas][day].size(); les++) {
                            if (teachForClas[par][clas][s[par][clas][day][les]] == t) {
                                l = min(l, les);
                                r = max(r, les);
                                cnt++;
                            }
                        }
                        ans += (double)(r - l) * 5;
                    }
                }
            }
        }
        return ans;
    }

    int teacherRelax() {
        int ans = 0;
        for (int t = 0; t < backToTeach.size(); t++) {
            set<int> st;
            for (int par = 0; par < pars; par++) {
                for (int clas = 0; clas < s[par].size(); clas++) {
                    for (int day = 0; day < s[par][clas].size(); day++) {
                        for (int les = 0; les < s[par][clas][day].size(); les++) {
                            if (teachForClas[par][clas][s[par][clas][day][les]] == t) {
                                st.insert(day);
                            }
                        }
                    }
                }
            }
            if (st.size() == 6) {
                ans += 1e9;
            }
        }
        return ans;
    }

    int noskip() {
        int ans = 0;
        for (int par = 0; par < pars; par++) {
            for (int clas = 0; clas < s[par].size(); clas++) {
                for (int day = 0; day < s[par][clas].size(); day++) {
                    for (int les = 0; les < s[par][clas][day].size() - 3; les++) {
                        if (s[par][clas][day][les] == -1) {
                            ans += 5000;
                        }
                    }
                }
            }
        }
        return ans;
    }

    int fizra() {
        int ans = 0;
        for (int day = 0; day < 5; day++) {
            for (int les = 0; les < maxWorkDays; les++) {
                map<int, int> cnt;
                for (int par = 0; par < s.size(); par++) {
                    for (int clas = 0; clas < s[par].size(); clas++) {
                        if (s[par][clas][day][les] != 15) continue;
                        ans -= cnt[teachForClas[par][clas][s[par][clas][day][les]]] * 1e9;
                        cnt[teachForClas[par][clas][s[par][clas][day][les]]]++;
                    }
                }
            }
        }
        int day = 5;
        for (int les = 0; les < maxSatDays; les++) {
            map<int, int> cnt;
            for (int par = 0; par < s.size(); par++) {
                for (int clas = 0; clas < s[par].size(); clas++) {
                    if (s[par][clas][day][les] != 15) continue;
                    ans -= cnt[teachForClas[par][clas][s[par][clas][day][les]]] * 1e9;
                    cnt[teachForClas[par][clas][s[par][clas][day][les]]]++;
                }
            }
        }
        return ans;
    }

    int threeInDay() {
        int ans = 0;
        for (int par = 0; par < pars; par++) {
            for (int clas = 0; clas < s[par].size(); clas++) {
                for (int day = 0; day < s[par][clas].size(); day++) {
                    map<int, int> cnt;
                    for (int les = 0; les < s[par][clas][day].size() - 3; les++) {
                        cnt[s[par][clas][day][les]]++;
                    }
                    for (auto [l, r] : cnt) {
                        ans += max(0ll, r - 3) * 1e10;
                        ans += max(0ll, r - 2) * 1e7;
                    }
                }
            }
        }
        return ans;
    }

    int getLoss() {
        return Pers() + teacherRelax() + fizra() + noskip() + threeInDay() + comfort();
    }

    void EVERY_DAY_IAM_SHUFFELING() {
        for (int i = 0; i < 1e6; i++) {
            int par = abs((int)rng()) % s.size();
            int clas = abs((int)rng()) % s[par].size();
            int day1 = abs((int)rng()) % s[par][clas].size();
            int day2 = abs((int)rng()) % s[par][clas].size();
            int les1 = abs((int)rng()) % s[par][clas][day1].size();
            int les2 = abs((int)rng()) % s[par][clas][day2].size();
            swap(s[par][clas][day1][les1], s[par][clas][day2][les2]);
            par = abs((int)rng()) % s.size();
            clas = abs((int)rng()) % s[par].size();
            int les = abs((int)rng()) % backToSubj.size();
            int nw = teach[subj[teachForClas[par][clas][les]]][abs((int)rng()) % teach[subj[teachForClas[par][clas][les]]].size()];
            teachForClas[par][clas][les] = nw;
        }
    }

    void OTZHIGAY_TRATATATATA() {
        //freopen("output.txt", "w", stdout);
        double d = 0.99999;
        int cnt = 0;
        int already = 0;
        for (double temperature = 1e8; getLoss() > 5e8; temperature *= d) {
            cnt++;
            dule last = *this;
                int par = abs((int)rng()) % s.size();
                int clas = abs((int)rng()) % s[par].size();
                int day1 = abs((int)rng()) % s[par][clas].size();
                int day2 = abs((int)rng()) % s[par][clas].size();
                int les1 = abs((int)rng()) % s[par][clas][day1].size();
                int les2 = abs((int)rng()) % s[par][clas][day2].size();
                swap(s[par][clas][day1][les1], s[par][clas][day2][les2]);
                par = abs((int)rng()) % s.size();
                clas = abs((int)rng()) % s[par].size();
                int les = abs((int)rng()) % backToSubj.size();
                int nw = teach[subj[teachForClas[par][clas][les]]][abs((int)rng()) % teach[subj[teachForClas[par][clas][les]]].size()];
                teachForClas[par][clas][les] = nw;
            if (getLoss() > last.getLoss()) {
                s = last.s;
                already++;
                teachForClas = last.teachForClas;
            } else if (((double) rand() / RAND_MAX) >= exp(((double)last.getLoss() - getLoss()) / temperature)) {
                s = last.s;
                teachForClas = last.teachForClas;
            }
            if (already == 40000) {
                temperature *= 2;
                already = 0;
            }
        //    cout << cnt << " " << getLoss() << endl;
        }
        //fclose(stdout);
    }


    void output() {
        for (int par = 0; par < s.size(); par++) {
            for (int clas = 0; clas < s[par].size(); clas++) {
                cout << par + 7;
                cout << "." << clas + 1 << ":" << endl;
                for (int day = 0; day < 6; day++) {
                    cout << "Day " << day + 1 << ": ";
                    for (int les = 0; les < s[par][clas][day].size(); les++) {
                        if (s[par][clas][day][les] == -1) {
                            cout << "- ";
                            continue;
                        }
                        cout << backToSubj[s[par][clas][day][les]] << "-" << backToTeach[teachForClas[par][clas][s[par][clas][day][les]]] << " ";
                    }
                    cout << endl;
                }
                cout << endl;
            }
            cout << endl << endl;
        }
    }
};
