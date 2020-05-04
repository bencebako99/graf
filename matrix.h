#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <initializer_list>
#include <cmath>
#include <ostream>
#include <sstream>
#include <fstream>
#include <string>
#include <istream>

using namespace std;
template <typename T>

struct Matrix
{
    int N;
    std::vector<T> data;
    ~Matrix(){};

    //Subscription operator
    T& operator()(int i, int j) {return data[(i*N)+j]; }
    T const& operator() (int i, int j) const {return data[(i*N)+j]; }
    //Function call operator
    T& operator[](int i) {return data[i];}
    T const& operator[] (int i) const {return data[i]; }
};

//Addition operators 4 versions for all combinations of const& and &&:
template <typename T>
Matrix<T> operator+(Matrix<T> const& A, Matrix<T> const& B){
    Matrix<T> result; result.data.resize(A.N*A.N);
    result.N = A.N;
    for(int i=0; i<A.N; i++){
        for(int j=0; j<A.N; j++)
            result.data[i*result.N+j]=A.data[i*A.N+j]+B.data[i*A.N+j];
    }
    return result;
}
template <typename T>
Matrix<T>&& operator+(Matrix<T> && A, Matrix<T> && B){
    for(int i=0; i<A.N; i++){
        for(int j=0; j<A.N; j++)
            A.data[i*A.N+j]+=B.data[i*B.N+j];
    }
    return std::move(A);
}
template <typename T>
Matrix<T>&& operator+(Matrix<T> && A, Matrix<T> const& B){
    for(int i=0; i<A.N; i++){
        for(int j=0; j<A.N; j++)
            A.data[i*A.N+j]+=B.data[i*B.N+j];
    }
    return std::move(A);
}
template <typename T>
Matrix<T>&& operator+(Matrix<T> const& A, Matrix<T> && B){
    for(int i=0; i<A.N; i++){
        for(int j=0; j<A.N; j++)
            B.data[i*B.N+j]+=A.data[i*A.N+j];
    }
    return std::move(B);
}


//- operators 4 versions for all combinations of const& and &&:
template <typename T>
Matrix<T> operator-(Matrix<T> const& A, Matrix<T> const& B){
    Matrix<T> result; result.data.resize(A.N*A.N);
    result.N = A.N;
    for(int i=0; i<A.N; i++){
        for(int j=0; j<A.N; j++)
            result.data[i*result.N+j]=A.data[i*A.N+j]-B.data[i*B.N+j];
    }

    return result;
}
template <typename T>
Matrix<T>&& operator-(Matrix<T> && A, Matrix<T> && B){
    for(int i=0; i<A.N; i++){
        for(int j=0; j<A.N; j++)
            A.data[i*A.N+j]-=B.data[i*B.N+j];
    }
    return std::move(A);
}
template <typename T>
Matrix<T>&& operator-(Matrix<T> && A, Matrix<T> const& B){
    for(int i=0; i<A.N; i++){
        for(int j=0; j<A.N; j++)
            A.data[i*A.N+j]-=B.data[i*B.N+j];
    }
    return std::move(A);
}
template <typename T>
Matrix<T>&& operator-(Matrix<T> const& A, Matrix<T> && B){
    for(int i=0; i<A.N; i++){
        for(int j=0; j<A.N; j++)
            B.data[i*B.N+j]=A.data[i*A.N+j]-B.data[i*B.N+j];
    }
    return std::move(B);
}

// * operator
template <typename T>
Matrix<T> operator*(Matrix<T> const& A, int const& scal){
    Matrix<T> result; result.data.resize(A.N*A.N);
    result.N = A.N;
    for(int i=0; i<A.N; i++){
        for(int j=0; j<A.N; j++)
            result.data[i*A.N+j]=A.data[i*A.N+j]*scal;
    }
    return result;
}
template <typename T>
Matrix<T> operator*(int const& scal, Matrix<T> const& A){
    Matrix<T> result; result.data.resize(A.N*A.N);
    result.N = A.N;
    for(int i=0; i<A.N; i++){
        for(int j=0; j<A.N; j++)
            result.data[i*A.N+j]=A.data[i*A.N+j]*scal;
    }
    return result;
}
template <typename T>
Matrix<T>&& operator*(int const& scal, Matrix<T> && A){
    for(int i=0; i<A.N; i++){
        for(int j=0; j<A.N; j++)
            A.data[i*A.N+j]*=scal;
    }
    return std::move(A);
}
template <typename T>
Matrix<T>&& operator*(Matrix<T> && A, int const& scal){
    for(int i=0; i<A.N; i++){
        for(int j=0; j<A.N; j++)
            A.data[i*A.N+j]*=scal;
    }
    return std::move(A);
}


// / operator
template <typename T>
Matrix<T> operator/(Matrix<T> const& A, int const& scal){
    Matrix<T> result; result.data.resize(A.N*A.N);
    result.N = A.N;
    for(int i=0; i<A.N; i++){
        for(int j=0; j<A.N; j++)
            result.data[i*A.N+j]=A.data[i*A.N+j]/scal;
    }
    return result;
}
template <typename T>
Matrix<T>&& operator/(Matrix<T> && A, int const& scal){
    for(int i=0; i<A.N; i++){
        for(int j=0; j<A.N; j++)
            A.data[i*A.N+j]/=scal;
    }
    return std::move(A);
}

//matrix multiplication 4 versions for all combinations of const& and &&:
template <typename T>
Matrix<T> operator*(Matrix<T> const& A, Matrix<T> const& B){
    Matrix<T> result; result.data.resize(A.N*A.N);
    result.N = A.N;
    for(int i=0; i<A.N; i++){
        for(int j=0; j<A.N; j++){
            for(int k=0; k<A.N; k++){
                result.data[i*result.N+j]+=A.data[i*A.N+k]*B.data[k*A.N+j];
            }
        }
    }
    return result;
}
template <typename T>
Matrix<T>&& operator*(Matrix<T> && A, Matrix<T> && B){
    Matrix<T> result; result.data.resize(A.N*A.N);
    result.N = A.N;
    for(int i=0; i<A.N; i++){
        for(int j=0; j<A.N; j++){
            for(int k=0; k<A.N; k++){
                result.data[i*result.N+j]+=A.data[i*A.N+k]*B.data[k*A.N+j];
            }
        }
    }
    for(int i=0; i<A.N; i++){
        for(int j=0; j<A.N; j++)
            A.data[i*A.N+j]=result[i*A.N+j];
    }
    return std::move(A);
}
template <typename T>
Matrix<T>&& operator*(Matrix<T> && A, Matrix<T> const& B){
    Matrix<T> result; result.data.resize(A.N*A.N);
    result.N = A.N;
    for(int i=0; i<A.N; i++){
        for(int j=0; j<A.N; j++){
            for(int k=0; k<A.N; k++){
                result.data[i*result.N+j]+=A.data[i*A.N+k]*B.data[k*A.N+j];
            }
        }
    }
    for(int i=0; i<A.N; i++){
        for(int j=0; j<A.N; j++)
            A.data[i*A.N+j]=result[i*A.N+j];
    }
    return std::move(A);
}
template <typename T>
Matrix<T>&& operator*(Matrix<T> const& A, Matrix<T> && B){
    Matrix<T> result; result.data.resize(A.N*A.N);
    result.N = A.N;
    for(int i=0; i<A.N; i++){
        for(int j=0; j<A.N; j++){
            for(int k=0; k<A.N; k++){
                result.data[i*result.N+j]+=A.data[i*A.N+k]*B.data[k*A.N+j];
            }
        }
    }
    for(int i=0; i<A.N; i++){
        for(int j=0; j<A.N; j++)
            B.data[i*B.N+j]=result[i*B.N+j];
    }
    return std::move(B);
}

template <typename T>
 ostream& operator<<(std::ostream& o, Matrix<T> const& M){
        o << M.N << endl;
        for(int i=0; i<M.N; i++){
            for(int j=0; j<M.N ; j++){
                o << M[i*M.N+j] << " ";
            }
            o << endl;
        }
        return o;
    }
template <typename T>
istream& operator>>(std::istream& s, Matrix<T>& M){
    const auto state = s.rdstate();
    const auto pos = s.tellg();
    string tmp;
    getline(s, tmp);
    if(tmp.size()>0){
        stringstream ss(tmp);
        getline(ss, tmp);  M.N= stod(tmp);
        for(int i=0; i<M.N; i++){
            getline(s, tmp);
            stringstream ss1(tmp);
            for(int j=0; j<M.N; j++){
                getline(ss1, tmp, ' ');  M.data.push_back(stod(tmp));
            }
        }
    }
    else{
        s.clear();
        s.seekg(pos);
        s.setstate(state);
    }
    return s;
}
