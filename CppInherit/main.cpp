int main()
{
	SpreadsheetCell* cellArray[3];
	cellArray[0] = new StringSpreadsheetCell();
	cellArray[1] = new StringSpreadsheetCell();
	cellArray[2] = new DoubleSpreadsheetCell();
	
	cellArray[0]->set("hello");
	cellArray[1]->set("10");
	cellArray[2]->set("18");
	
	cout << "Array values are [" << cellArray[0]->getString() << ", " <<
									cellArray[1]->getString() << ", " <<
									cellArray[2]->getString() << "] " <<
									endl;
									
	return 0;
}