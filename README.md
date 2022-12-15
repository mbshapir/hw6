To compile and test in terminal:

str-hash-test:
cd hw6/ g++ -g str-hash-test.cpp -o str-hash-test/ ./str-hash-test example 
(where example is the input you want to test)

ht-test:
cd hw6/ g++ -g ht-test.cpp -o ht-test/ ./ht-test
(change values in ht-test.cpp file to test more)

boggle-test
cd hw6/ g++ -g boggle-driver.cpp -o boggle-driver/ ./boggle-driver x y dict.txt
(replace x and y with row/columns you'd like to use for testing)