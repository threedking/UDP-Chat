//---------------------------------------------------------------------------

#ifndef ModelsH
#define ModelsH

#include "Messages.h"
#include <set>
#include <mutex>
//---------------------------------------------------------------------------
template <typename T>
class Model{
private:
	std::multiset<T> Data;
	std::mutex Mutex;
public:

Model(){}
//----------------------------
void AddData(T newData){
std::lock_guard<std::mutex> lock(this->Mutex);
this->Data.insert(newData);
}
//----------------------------
void DeleteAllData(){
std::lock_guard<std::mutex> lock(this->Mutex);
this->Data.clear();
}
//----------------------------
std::multiset<T> GetAllData(){
std::lock_guard<std::mutex> lock(this->Mutex);
return this->Data;
}
//----------------------------
std::multiset<T> GetFewOfLastData(int Amount){
std::lock_guard<std::mutex> lock(this->Mutex);
if(Amount<=this->Data.size()){
	return this->Data;
}else{
	auto it=this->Data.rbegin();
	std::advance(it,Amount);
	return std::multiset<T>(this->Data.rbegin(),it);
}
}
//----------------------------
int GetCountOfData(){
std::lock_guard<std::mutex> lock(this->Mutex);
	return this->Data.size();
}
//----------------------------
void DeleteOne(T Other){
std::lock_guard<std::mutex> lock(this->Mutex);
Data.erase(Other);
}
//----------------------------
};
//---------------------------------------------------------------------------
#endif
