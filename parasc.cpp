#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string_view>

static const void write_hex(std::ofstream& out, char opres = 0x0){
    out.write(reinterpret_cast<char*>(&opres), sizeof(unsigned char));
}

bool is_hex(const std::string_view &v) {
  return std::all_of(std::begin(v), std::end(v), [] (unsigned char c) { return std::isxdigit(c); });
}

typedef enum{
    //Add to accumulator.
    SPS_ADD = 0xA0,
    //Subtract from accumulator.
    SPS_SUB = 0xA1,
    //Push to stack.
    SPS_PSH = 0xB0,
    //Pop off stack to Accumulator, X or Y registers, or to the void.
    SPS_POP = 0xB1,
    //Halt!
    SPS_HLT = 0xF0,
    //Dump current state of VM.
    SPS_STT = 0xF1
}CMDS;

void read_source(std::ifstream& file, const std::string& name){
    std::ofstream output(name + ".spc", std::ios::binary);
    std::vector<std::string> operations;
    std::string buffer;
    //Loop through each line *on a buffer* and delimitate with whitespace.
    while(getline(file, buffer)){
        std::stringstream ss(buffer);
        while(getline(ss, buffer, ' ')){
            printf("%s\n", buffer.c_str());
            operations.push_back(buffer);
        }
    }
    file.close();
    for(auto& op : operations){
        char opres = 0x0;
        if(op == "ADD"){
            write_hex(output, SPS_ADD);
        }
        else if(op == "SUB"){
            write_hex(output, SPS_SUB);
        }
        else if(is_hex(op)){
            write_hex(output, strtoul(op.c_str(), nullptr, 16));
        }
        else if(op == "PSH"){
            write_hex(output, SPS_PSH);
        }
        else if(op == "POP"){
            write_hex(output, SPS_POP);
        }
        else if(op == "STT"){
            write_hex(output, SPS_STT);
            write_hex(output);
        }else if(op == "HLT"){
            write_hex(output, SPS_HLT);
            write_hex(output);
        }else{
            printf("Uh, what is %s anyways?\n", op.c_str());
        }
        
    }
    output.close();
}

void print_out_help(){
    printf("[paraphenalia] [?-h] input\n-h = Prints out this very helper.\ninput = Give to paraphenalia the path of the Spinscript source.\n");
}

int main(int argc, char** argv){
    //Read off common_unfortunes.
    if(argc > 1){
        if(!strcmp(argv[1], "-h")){
            print_out_help();
        }
        else{
            std::string the_path = argv[1];
            std::ifstream file(the_path);
            if(file.is_open()){
                
                std::string::size_type const p(the_path.find_last_of('.'));
                std::string file_without_extension = the_path.substr(0, p);
                read_source(file,file_without_extension);
            }
            else{
                fprintf(stderr, "Path invalid...\n");
                return -1;
            } 
        }
    }
    else{
        return -1;
    }
    return 0;
}