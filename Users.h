//---------------------------------------------------------------------------
#ifndef UsersH
#define UsersH
//---------------------------------------------------------------------------
class User{
private:
	std::string IP="127.0.0.1";
	std::string Name="User";
	bool IsOnline;

	void SetIP(std::string newIP);
	void SetName(std::string newName);
public:
	User(){};
	User(std::string newIP, std::string newName);

	void SetIsOnline(bool newIsOnline);

	std::string GetIP()const;
	std::string GetName()const;
	bool GetIsOnline()const;

	bool operator<(const User& Other)const;
	bool operator==(const User& Other)const;
};
//---------------------------------------------------------------------------
#endif
