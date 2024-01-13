#pragma once

class NibbleArray {

public:
    NibbleArray();
    NibbleArray(unsigned int _size);
    ~NibbleArray();
    
    void init(unsigned int _size, unsigned char initialData);

    void set(unsigned int index, unsigned char data);
    unsigned char get(unsigned int index) const;

private:
    unsigned char* data;
    unsigned int size;

};