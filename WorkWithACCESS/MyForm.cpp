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
	OleDbCommand^ dbCommand = gcnew OleDbCommand(query, dbConnection); //Выполнение команды
	OleDbDataReader^ dbReader = dbCommand->ExecuteReader(); //считываем данные

	
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
	//Выбор нужно строки для добавления 
	if (dataGridView1->SelectedRows->Count != 1) {
		MessageBox::Show("Выбирите одну строку для добавления!","Внимание!");
		return;
	}
	//Узнаем номер строки которую нужно добавить

	int index = dataGridView1->SelectedRows[0]->Index;
	
	//Проверяем данные
	if (dataGridView1->Rows[index]->Cells[0]->Value == nullptr ||
		dataGridView1->Rows[index]->Cells[1]->Value == nullptr ||
		dataGridView1->Rows[index]->Cells[2]->Value == nullptr ||
		dataGridView1->Rows[index]->Cells[3]->Value == nullptr ) {
		MessageBox::Show("Не все данные введены!","Внимание!");
		return;
	}
	
	//Считываем данные

	String^ id       = dataGridView1->Rows[index]->Cells[0]->Value->ToString();
	String^ name     = dataGridView1->Rows[index]->Cells[1]->Value->ToString();
	String^ cost     = dataGridView1->Rows[index]->Cells[2]->Value->ToString();
	String^ quantiti = dataGridView1->Rows[index]->Cells[3]->Value->ToString();

	//подключение к БД
	String^ connectionString = "provider=Microsoft.ACE.OLEDB.12.0;Data Source=Test.mdb"; //строка подключения 
	OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);

	//выполнить запрос к БД
	dbConnection->Open(); //открываем соединение

	String^ query = "INSERT INTO [table_name] VALUES (" + id + ", '" + name + "', " + cost + ", " + quantiti + ")"; //Текст завпрос
	OleDbCommand^ dbCommand = gcnew OleDbCommand(query, dbConnection); //Выполнение команды
	
	if (dbCommand->ExecuteNonQuery() != 1)
		MessageBox::Show("Ошибка выполнения запроса!", "Внимание!");
	else
		MessageBox::Show("Данные введены!", "Готово!");

	//Закрываем соединение
	dbConnection->Close();

	return System::Void();
}

System::Void WorkWithACCESS::MyForm::button_update_Click(System::Object^ sender, System::EventArgs^ e)
{
	//Выбор нужно строки для добавления 
	if (dataGridView1->SelectedRows->Count != 1) {
		MessageBox::Show("Выбирите одну строку для добавления!", "Внимание!");
		return;
	}
	//Узнаем номер строки которую нужно добавить

	int index = dataGridView1->SelectedRows[0]->Index;

	//Проверяем данные
	if (dataGridView1->Rows[index]->Cells[0]->Value == nullptr ||
		dataGridView1->Rows[index]->Cells[1]->Value == nullptr ||
		dataGridView1->Rows[index]->Cells[2]->Value == nullptr ||
		dataGridView1->Rows[index]->Cells[3]->Value == nullptr) {
		MessageBox::Show("Не все данные введены!", "Внимание!");
		return;
	}

	//Считываем данные

	String^ id = dataGridView1->Rows[index]->Cells[0]->Value->ToString();
	String^ name = dataGridView1->Rows[index]->Cells[1]->Value->ToString();
	String^ cost = dataGridView1->Rows[index]->Cells[2]->Value->ToString();
	String^ quantity = dataGridView1->Rows[index]->Cells[3]->Value->ToString();

	//подключение к БД
	String^ connectionString = "provider=Microsoft.ACE.OLEDB.12.0;Data Source=Test.mdb"; //строка подключения 
	OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);

	//выполнить запрос к БД
	dbConnection->Open(); //открываем соединение

	String^ query = "UPDATE [table_name] SET Name = '" + name + "', Cost = " + cost + ", Quantity = " + quantity + " WHERE id =" + id; //Текст завпрос
	OleDbCommand^ dbCommand = gcnew OleDbCommand(query, dbConnection); //Выполнение команды

	if (dbCommand->ExecuteNonQuery() != 1)
		MessageBox::Show("Ошибка выполнения запроса!", "Внимание!");
	else
		MessageBox::Show("Данные введены!", "Готово!");

	//Закрываем соединение
	dbConnection->Close();

	return System::Void();
}

System::Void WorkWithACCESS::MyForm::button_delete_Click(System::Object^ sender, System::EventArgs^ e)
{
	//Выбор нужно строки для добавления 
	if (dataGridView1->SelectedRows->Count != 1) {
		MessageBox::Show("Выбирите одну строку для добавления!", "Внимание!");
		return;
	}
	//Узнаем номер строки которую нужно добавить

	int index = dataGridView1->SelectedRows[0]->Index;

	//Проверяем данные
	if (dataGridView1->Rows[index]->Cells[0]->Value == nullptr) {
		MessageBox::Show("Не все данные введены!", "Внимание!");
		return;
	}

	//Считываем данные

	String^ id = dataGridView1->Rows[index]->Cells[0]->Value->ToString();

	//подключение к БД
	String^ connectionString = "provider=Microsoft.ACE.OLEDB.12.0;Data Source=Test.mdb"; //строка подключения 
	OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);

	//выполнить запрос к БД
	dbConnection->Open(); //открываем соединение

	String^ query = "DELETE FROM [table_name] WHERE id =" + id; //Текст завпрос
	OleDbCommand^ dbCommand = gcnew OleDbCommand(query, dbConnection); //Выполнение команды

	if (dbCommand->ExecuteNonQuery() != 1)
		MessageBox::Show("Ошибка выполнения запроса!", "Внимание!");
	else {
		MessageBox::Show("Данные удалены!", "Готово!");
		//удаление строки из таблицы
		dataGridView1->Rows->RemoveAt(index);
	}
		

	//Закрываем соединение
	dbConnection->Close();
	return System::Void();
}

