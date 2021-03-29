#include "MyForm.h"
#include <string>

using namespace System;
using namespace System::Windows::Forms;
using namespace WorkWithACCESS;
using namespace System::Data::OleDb;

[STAThread]



int main(array<String^>^ arg) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew MyForm());
}

System::Void WorkWithACCESS::MyForm::dataGridView1_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
{
	return System::Void();
}

System::Void WorkWithACCESS::MyForm::groupBox1_Enter(System::Object^ sender, System::EventArgs^ e)
{
	return System::Void();
}

System::Void WorkWithACCESS::MyForm::выходToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	Application::Exit();
}

System::Void WorkWithACCESS::MyForm::обПрограммеToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	MessageBox::Show("тест");
}

System::Void WorkWithACCESS::MyForm::button_download_Click(System::Object^ sender, System::EventArgs^ e)
{
	//подключение к БД
	String^ connectionString = "provider=Microsoft.ACE.OLEDB.12.0;Data Source=Test.mdb"; //строка подключения 
	OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);

	//выполнить запрос к БД
	dbConnection->Open(); //открываем соединение

	String^ query = "SELECT * FROM [table_name]"; //Текст завпрос
	OleDbCommand^ dbComand = gcnew OleDbCommand(query, dbConnection); //Выполнение команды
	OleDbDataReader^ dbReader = dbComand->ExecuteReader(); //считываем данные

	
	//Проверяем данные
	if (!dbReader->HasRows) {
		MessageBox::Show("Ошибка");
	}
	else {
	//Заполняем данные в таблицу
		while (dbReader->Read()) {
			
			System::Windows::Forms::DataGridViewRow^ row = gcnew System::Windows::Forms::DataGridViewRow();
			row->CreateCells(dataGridView1);
			System::Windows::Forms::DataGridViewCellCollection^ cells = row->Cells;

			for (int i = 0; i < dbReader->FieldCount; i++) {
				System::Windows::Forms::DataGridViewTextBoxCell^ gridCell = gcnew System::Windows::Forms::DataGridViewTextBoxCell();
				gridCell->Value = dbReader[i];
				cells[i]=gridCell;
			}

			dataGridView1->Rows->Add(row);
		}
	}

	//Закрываем соединение
	dbReader->Close();
	dbConnection->Close();


	return System::Void();
}

System::Void WorkWithACCESS::MyForm::button_add_Click(System::Object^ sender, System::EventArgs^ e)
{
	return System::Void();
}

System::Void WorkWithACCESS::MyForm::button_update_Click(System::Object^ sender, System::EventArgs^ e)
{
	return System::Void();
}

System::Void WorkWithACCESS::MyForm::button_delete_Click(System::Object^ sender, System::EventArgs^ e)
{
	return System::Void();
}

