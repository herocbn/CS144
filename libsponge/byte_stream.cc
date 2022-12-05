#include "byte_stream.hh"

#include <algorithm>
#include <iterator>
#include <stdexcept>

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}
/*
using namespace std;

ByteStream::ByteStream(const size_t capacity) { DUMMY_CODE(capacity); }

size_t ByteStream::write(const string &data) {
    DUMMY_CODE(data);
    return {};
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    DUMMY_CODE(len);
    return {};
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) { DUMMY_CODE(len); }
*/
using namespace std;

ByteStream::ByteStream(const size_t capacity): _capacity(capacity),_data{}{}

size_t ByteStream::write(const string &data) {
   // DUMMY_CODE(data);
   auto sz = data.size();
   if(sz+_data.size()>_capacity){
        sz = _capacity-_data.size();
   }
   _wr_num+=sz;
    for(size_t i=0;i<sz;i++){
        _data.emplace_back(data[i]);
    }
   return sz;

}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
  // DUMMY_CODE(len);
    string str;
    str.assign(_data.begin(),_data.begin()+len);
    return str;
}

void ByteStream::end_input() {
    _wr_eof = true;
}
void ByteStream::pop_output(const size_t len) { 
    // DUMMY_CODE(len); 
    int i = len;
    while(i){
        i--;
        _data.pop_front();
    }
    _rd_num+=len;
}

bool ByteStream::input_ended() const { return _wr_eof; }

size_t ByteStream::buffer_size() const { return _data.size(); }

bool ByteStream::buffer_empty() const {
    if(remaining_capacity() == _capacity){
        return true;
    }
    return false;
 }

bool ByteStream::eof() const { return  buffer_empty() && input_ended(); }

size_t ByteStream::bytes_written() const { return {_wr_num}; }

size_t ByteStream::bytes_read() const { return {_rd_num}; }

size_t ByteStream::remaining_capacity() const { return _capacity-_data.size(); }
