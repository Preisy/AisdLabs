#ifndef LAB_5_DIGRAPH_H
#define LAB_5_DIGRAPH_H

#include <fstream>
#include "lib.h"
#include "iostream"
#include <limits>

class Digraph {
private:
    lib::DynamicArray<lib::DynamicArray<int>> matrix;

public:
    /**
     * @param [in] u1 - start point
     * @param [in] u2 - end point
     * */
    lib::Array<int> findShortestPath(int u1, int u2) {
        if (u1 >= matrix.getLength() ||
            u2 < 0 ||
            u2 >= matrix.getLength() ||
            u2 < 0) {
            return lib::Array<int>(0);
        }

        lib::Array<int> path(matrix.getLength());
        for (int i = 0; i < path.getLength(); ++i)
            path[i] = std::numeric_limits<int>::max();

        lib::Queue<int> q;

        path[u1] = 0;
        q.push(u1);


        while (!q.empty()) {
            int el = q.pop();
            for (int i = 0; i < matrix.getLength(); ++i) {
                if (matrix[el][i] == 1) {
                    if (path[i] > path[el] + 1) {
                        path[i] = path[el] + 1;
                        int a = path[i];
                        if (i != u2)
                            q.push(i);
                    }
                }
            }
        }

        lib::DynamicArray<int> arr;
        arr.push(u2);
        for (int it = u2; it != u1;) {
            int dist = std::numeric_limits<int>::max();
            int node = -1;
            for (int i = 0; i < matrix.getLength(); ++i) {
                if (matrix[i][it] == 1) {
                    if (dist > path[i]) {
                        dist = path[i];
                        node = i;
                    }
                }
            }
            if (node == -1) {
                return lib::Array<int>(0);
            }
            arr.push(node);
            it = node;
        }

        lib::Array<int> res(arr.getLength());
        for (int i = 0; i < arr.getLength(); ++i) {
            res[i] = arr[arr.getLength() - i - 1];
        }

        return res;
    }


private:
    enum Color {
        white,
        grey,
        black
    };
public:
    /**
     * @param [in] u1 - start point
     * @param [in] u2 - end point
     * */
    lib::Array<int> findPath(int u1, int u2) {
        if (u1 >= matrix.getLength() ||
            u2 < 0 ||
            u2 >= matrix.getLength() ||
            u2 < 0) {
            return lib::Array<int>(0);
        }

        lib::Array<int> color(matrix.getLength());
        for (int i = 0; i < color.getLength(); ++i) color[i] = Color::white;
        lib::Array<int> path(matrix.getLength());
        for (int i = 0; i < path.getLength(); ++i) path[i] = -1;

        if (!recFindPath(u1, u2, color, path)) {
            return lib::Array<int>(0);
        }

        int len = 0;
        int i = u2;
        while(i != -1) {
            len += 1;
            if (i == path[i]) break;
            i = path[i];
        }

        lib::Array<int> res(len);
        i = u2;
        for (int j = 0; j < len; ++j) {
            res[len - j - 1] = i;
            i = path[i];
        }

        return res;
    }

private:
    bool recFindPath(int u1, int u2, lib::Array<int> & color, lib::Array<int> & path) {
        color[u1] = Color::grey;
        for (int i = 0; i < matrix.getLength(); ++i) {
            if (matrix[u1][i] == 1) {
                if (i == u2) {
                    path[i] = u1;
                    return true;
                }
                if (color[i] == Color::white) {
                    path[i] = u1;
                    if (recFindPath(i, u2, color, path))
                        return true;
                }
            }
        }
        color[u1] = Color::black;
        return false;
    }

public:
    bool deleteEdge(int u1, int u2) {
        if (u1 >= matrix.getLength() ||
            u2 < 0 ||
            u2 >= matrix.getLength() ||
            u2 < 0) {
            return false;
        }

        matrix[u1][u2] = 0;
//        matrix[u2][u1] = 0;
        return true;
    }

    bool deleteVertex(int u) {
        if (u >= matrix.getLength() || u < 0)
            return false;
        for (int i = 0; i < matrix.getLength(); ++i) {
            matrix[i][u] = 0;
            matrix[u][i] = 0;
        }
        return true;
    }

    void addVertex(int u, const lib::Array<int> & arr) {
        for (int i = 0; i < arr.getLength(); ++i) {
            if (arr[i] >= matrix.getLength() || u >= matrix.getLength()) {
                int max = u;
                for (int j = i; j < arr.getLength(); ++j) {
                    if (arr[j] > max) max = arr[j];
                }
                resizeMatrix(max + 1);
            }
            matrix[u][arr[i]] = 1;
        }
    }

    void addEdge(int u1, int u2) {
        int max = u1 > u2 ? u1 : u2;
        if (max >= matrix.getLength()) {
            resizeMatrix(max + 1);
        }
        matrix[u1][u2] = 1;
    }


private:
    void resizeMatrix(int n) {
        lib::DynamicArray<lib::DynamicArray<int>> tmp(n);
        int minLen = n > matrix.getLength() ? matrix.getLength() : n;

        for (int i = 0; i < n; ++i) {
            tmp[i] = lib::DynamicArray<int>(n);
            for (int j = 0; j < n; ++j) {
                tmp[i][j] = 0;
            }
        }




        for (int i = 0; i < minLen; ++i) {
            tmp[i] = lib::DynamicArray<int>(n);
            for (int j = 0; j < minLen; ++j) {
                tmp[i][j] = std::move(matrix[i][j]);
            }
            for (int j = minLen; j < n; ++j) {
                tmp[i][j] = 0;
            }
        }
        matrix = std::move(tmp);
    }

public:
    void print() const {
        lib::Array<std::string> symbols(7);
        symbols[0] = "─";
        symbols[1] = "│";
        symbols[2] = "┌";
        symbols[3] = "┐";
        symbols[4] = "┘";
        symbols[5] = "└";
        symbols[6] = "■";
//        symbols[0] = (char) 196;
//        symbols[1] = (char) 179;
//        symbols[2] = (char) 218;
//        symbols[3] = (char) 191;
//        symbols[4] = (char) 217;
//        symbols[5] = (char) 192;
//        symbols[5] = (char) 254;


        if (matrix.getLength() == 0) return;

        int maxLen = (int) std::to_string(matrix.getLength()).size();
        std::cout << "  ";
        for (int i = 0; i < matrix.getLength(); ++i) {
            std::string str = std::to_string(i);
            for (int k = str.size(); k < maxLen; ++k)
                str += ' ';
            std::cout << str << " ";
        }
        std::cout << '\n';
        for (int j = 0; j < maxLen; ++j)
            std::cout << ' ';
        std::cout << symbols[2];
        for (int i = 0; i < matrix.getLength(); ++i) {
            for (int j = 0; j < maxLen; ++j)
                std::cout << symbols[0];
            std::cout << symbols[0];
        }
        std::cout << symbols[3];


        std::cout << '\n';

        for (int i = 0; i < matrix.getLength(); ++i) {
            std::cout << i;
            for (int j = std::to_string(i).size(); j < maxLen; ++j)
                std::cout << ' ';
            std::cout << symbols[1];
            for (int j = 0; j < matrix.getLength(); ++j) {

                std::string str = matrix[i][j] == 0 ? " " : symbols[6];
                for (int k = 1; k < maxLen; ++k)
                    str += ' ';
                std::cout << str << " ";
            }
            std::cout << symbols[1] << '\n';
        }

        for (int j = 0; j < maxLen; ++j)
            std::cout << ' ';
        std::cout << symbols[5];
        for (int i = 0; i < matrix.getLength(); ++i) {
            for (int j = 0; j < maxLen; ++j)
                std::cout << symbols[0];
            std::cout << symbols[0];
        }
        std::cout << symbols[4];


        std::cout << '\n';


        std::cout << std::flush;
    }

    void write() const {
        std::ofstream fout("./tmp.dot", std::ios::out | std::ios_base::trunc);
        fout << "digraph myGraph{node[shape=circle,color=black,fontcolor=black,fontsize=10];";
        if (!fout.is_open()) {
            std::cout << "Файл не может быть открыт или создан\n";
            return;
        }
        if (matrix.getLength() == 0) {
            fout << "}";
            fout.close();
            system("dot tmp.dot | neato -n -Tpng -o graph.png");
        }

        for (int i = 0; i < matrix.getLength(); ++i) {
            for (int j = 0; j < matrix.getLength(); ++j) {
                if (matrix[i][j] == 1) {
                    fout << i << "->" << j << ";";
                }
            }
        }


        fout << "}";
        fout.close();
        system("dot tmp.dot | neato -n -Tpng -o graph.png");
//        system("rm -rf tmp.dot");
    }
};



#endif //LAB_5_DIGRAPH_H
