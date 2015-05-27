#include "SpreadsheetCell.h"

//前置声明 (在出现两个类相互需要包含的语义时应该使用前置声明)
class SpreadsheetApplication;
 
class Spreadsheet
{
	public:
		Spreadsheet(int inWidth, int inHeight);
		~Spreadsheet();
		Spreadsheet(const Spreadsheet& src);
		Spreadsheet& operator=(const Spreadsheet& rhs);
		void setCellAt(int x, int y, Spreadsheet &cell) const;
		SpreadsheetCell getCellAt(int x, int y);
		int getId() const;
		Spreadsheet(int inWidth, int inHeight, SpreadsheetApplication& theApp);
	protected:
		bool inRange(int val, int upper);
		int mWidth, mHeight;
		SpreadsheetCell** mCells;
		static int sCounter = 0;
		int mId;
		static const int kMaxHeight = 100;
		static const int kMaxWidth = 100;
		SpreadsheetApplication& mTheApp;
};

