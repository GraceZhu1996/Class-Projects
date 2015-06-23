package com.salakotolu.walletview;

import java.util.List;

import android.content.Context;
import android.util.Pair;

public class Data {
	Context context;
	DatabaseHandler Category;
	DatabaseHandler Settings;
	
	public Data(Context context){
		this.context = context;
		
	}
	
	public void Setup(){
		//Settings
		String[] s_columns = {"Option", "Value"};
		String[] s_datatype = {"Text", "Text"};
		Settings = new DatabaseHandler(context, "Settings", s_columns, s_datatype);

		Pair<List<String>, List<String>> settings = Settings.getValues_2_settings();
		if (settings.first.size() == 0){
			//If the app is being run for the first time.
			Settings.close();
			//TODO Run First run programs including intro and settings
			
			add_Temp_values();
		}else{
			
			
		}
	}
	
	private void add_Temp_values(){
		//TODO Temp data
		String[] i_columns = {"Item", "Amount", "Category", "Date"};
		String[] i_datatype = {"Text", "Double", "Text", "Text"};
		//myDatabase items = new myDatabase(context, "WalletViewData", "Items", i_columns, i_datatype, version);
		

		//Categories
		String[] c_columns = {"Category"};
		String[] c_datatype = {"Text"};
		Category = new DatabaseHandler(context, "Category", c_columns, c_datatype);
		String[] cat =  {"Food", "Enterntainment", "Shopping", "Eating", "Mortgage or rent", "Phone", "Electricity", "Gas", "Water and sewer", "Cable", "Waste removal",
        		"Maintenance or repairs", "Supplies"};
		Category.category_Add(cat);
		Category.close();		
	}
}
