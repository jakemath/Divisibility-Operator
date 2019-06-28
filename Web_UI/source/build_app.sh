g++ -std=c++14 bigint.h bigint.cpp bigint_application.h bigint_application.cpp bigint_application_main.C -lwthttp -lwt
./a.out --docroot . --http-address 0.0.0.0 --http-port 9090
