#include <fstream>

#include "Buffer.hpp"

namespace sjtu {

Buffer::Buffer(const std::filesystem::path& path){
    throw std::runtime_error("Not implemented.");
    //从path指向的文件构造Buffer,你需要打开文件并且把文件内容填充进Buffer,并正确初始化一些状态.
    //注意path可能为空的边界情况
}

Buffer::Buffer(std::vector<std::string> lines, std::filesystem::path path) {
    throw std::runtime_error("Not implemented.");
}

std::size_t Buffer::GetLineCount() const {
    //返回文件行数
    throw std::runtime_error("Not implemented.");
}

const std::string& Buffer::GetLineAt(std::size_t row) const {
    //返回第row行的内容
    throw std::runtime_error("Not implemented.");
}


std::string Buffer::GetDisplayName() const {
    //返回文件名,若是新文件,返回"[No Name]"
    throw std::runtime_error("Not implemented.");
}

bool Buffer::IsModified() const {
    //返回文件和上次保存比起来是否被修改过
    throw std::runtime_error("Not implemented.");
}

void Buffer::InsertCharacter(std::size_t row, std::size_t column, char value) {
    //在第row行第col列插入一个value, 注意越界检查
   throw std::runtime_error("Not implemented.");
}

void Buffer::EraseCharacter(std::size_t row, std::size_t column) {
   //在第row行第col列删除一个value
   throw std::runtime_error("Not implemented.");
}

void Buffer::SplitLine(std::size_t row, std::size_t column) {
    //在第row行第col列分割,即在此处敲了回车键
    throw std::runtime_error("Not implemented.");
}

void Buffer::JoinLine(std::size_t row) {
   //把第row + 1行合并进第row行
   throw std::runtime_error("Not implemented.");
}

void Buffer::Save() {
   //把文件内容保存, 直接调用WriteTo方法
   throw std::runtime_error("Not implemented.");
}

void Buffer::SaveAs(const std::filesystem::path& path) {
  throw std::runtime_error("Not implemented.");
}


void Buffer::WriteTo(const std::filesystem::path& path) const {
   //实际将缓冲区中的内容写入path指向的文件中
   throw std::runtime_error("Not implemented.");
}

} // namespace sjtu
