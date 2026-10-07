#include <fstream>
#include <stdexcept>

#include "Buffer.hpp"

namespace sjtu {

Buffer::Buffer(const std::filesystem::path& path){
    //从path指向的文件构造Buffer,你需要打开文件并且把文件内容填充进Buffer,并正确初始化一些状态.
    //注意path可能为空的边界情况
    path_ = path;
    if(path.empty() || !std::filesystem::exists(path)){
        lines_.push_back("");
    }
    else{
        std::ifstream file(path);
        if(!file.is_open()){
            throw std::runtime_error("Can not open file.");
        }
        std::string line;
        while(std::getline(file, line)){
            lines_.push_back(line);
        }
        if (file.bad()) {
            throw std::runtime_error("Can not read file.");
        }
        if(lines_.empty()) {
            lines_.push_back("");
        }
        else{
            empty_file = false;
        }
    }
}

Buffer::Buffer(std::vector<std::string> lines, std::filesystem::path path) {
    if(lines.empty()) {
        lines_.push_back("");
    }
    else {
        lines_ = lines;
        empty_file = false;
    }
    path_ = path;
}

std::size_t Buffer::GetLineCount() const {
    //返回文件行数
    return lines_.size();
}

const std::string& Buffer::GetLineAt(std::size_t row) const {
    //返回第row行的内容
    return lines_.at(row);
}


std::string Buffer::GetDisplayName() const {
    //返回文件名,若是新文件,返回"[No Name]"
    if(path_.empty()) return "[No Name]";
    return path_.filename().string();
}

bool Buffer::IsModified() const {
    //返回文件和上次保存比起来是否被修改过
    return modified;
}

void Buffer::InsertCharacter(std::size_t row, std::size_t column, char value) {
    //在第row行第col列插入一个value, 注意越界检查
    if(row < lines_.size() && column <= lines_[row].size()){
        lines_[row].insert(lines_[row].begin() + column, value);
        modified = true;
        empty_file = false;
    }
}

void Buffer::EraseCharacter(std::size_t row, std::size_t column) {
   //在第row行第col列删除一个value
   if(row < lines_.size() && column < lines_[row].size()){
    lines_[row].erase(lines_[row].begin() + column);
    modified = true;
    empty_file = false;
   }
}

void Buffer::SplitLine(std::size_t row, std::size_t column) {
    //在第row行第col列分割,即在此处敲了回车键
    if(row >= lines_.size() || column > lines_[row].size()) return;
    std::string s1 = lines_[row].substr(0, column), s2 = lines_[row].substr(column); 
    lines_[row] = s1;
    lines_.insert(lines_.begin() + row + 1, s2);
    modified = true;
    empty_file = false;
}

void Buffer::JoinLine(std::size_t row) {
   //把第row + 1行合并进第row行
    if(row >=lines_.size() || row >= lines_.size() - 1) return;
    lines_[row] = lines_[row] + lines_[row + 1];
    lines_.erase(lines_.begin() + row + 1);
    modified = true;
    empty_file = false;
}

void Buffer::Save() {
   //把文件内容保存, 直接调用WriteTo方法
   WriteTo(path_);
   modified = false;
}

void Buffer::SaveAs(const std::filesystem::path& path) {
    WriteTo(path);
    path_ = path;
    modified = false;
}


void Buffer::WriteTo(const std::filesystem::path& path) const {
   //实际将缓冲区中的内容写入path指向的文件中
    if (path.empty()) {
        throw std::runtime_error("No file name.");
    }
    std::ofstream file(path);
    if(!file.is_open()){
        throw std::runtime_error("Can not open file.");
    }
    if(!empty_file){
        for(const std::string& line : lines_){
            file << line << '\n';
        }
    }
    file.close();
    if(!file){
        throw std::runtime_error("Can not write file");
    }

}

} // namespace sjtu
