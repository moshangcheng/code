#include <fstream>
using namespace std;

int main() {
	//open with text format
	int num = 65536;
	char str[] = {"\nnew line"};

	ofstream unformatted_binary_out("C:\\Users\\shu\\Desktop\\unformatted_binary_out.txt", ios::binary);
	unformatted_binary_out.write((char*)&num, sizeof(num));
	unformatted_binary_out.write(str, sizeof(str));
	unformatted_binary_out.close();


	ofstream unformatted_text_out("C:\\Users\\shu\\Desktop\\unformatted_text_out.txt");
	unformatted_text_out.write((char*)&num, sizeof(num));
	unformatted_text_out.write(str, sizeof(str));

	ofstream binary_out("C:\\Users\\shu\\Desktop\\binary_out.txt", ios::binary);
	binary_out << num;
	binary_out << str;
	binary_out.close();


	ofstream text_out("C:\\Users\\shu\\Desktop\\text_out.txt");
	text_out << num;
	text_out << str;
	text_out.close();

	return 0;
}
