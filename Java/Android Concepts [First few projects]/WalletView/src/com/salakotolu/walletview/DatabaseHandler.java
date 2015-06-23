package com.salakotolu.walletview;

import java.text.Format;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Pair;

public class DatabaseHandler extends  SQLiteOpenHelper {
	static int dbVER = 1;
	static String NAME = "WalletViewData";
	String tableName;
	String[] col, data;
	Context context;
	
	public DatabaseHandler(Context context){
		super(context, NAME, null, dbVER);
	}
	
	public DatabaseHandler(Context context, String table, String[] columns, String[] datatype) {
		super(context, NAME, null, dbVER);
		tableName = table;
		col = columns;
		data = datatype;
	}

	@Override
	public void onCreate(SQLiteDatabase db) {
		String values = "";
		for (int i = 0; i < col.length; i++){
			if (i == 0 && col.length != i +1){
				values = col[i] + " " + data[i] + ",";
			}else if (i == col.length -1) {
				values = values + col[i] + " " + data[i];
			}else{
				values = values + col[i] + " " + data[i] + ",";
				
			}
			
		}
		if (col.length == 0){
			String CREATE_TABLE = "CREATE TABLE " + tableName + "("
	                + "ID" + " INTEGER PRIMARY KEY" + values + ")";
	        db.execSQL(CREATE_TABLE);
		}else{
		String CREATE_TABLE = "CREATE TABLE " + tableName + "("
	                + "ID" + " INTEGER PRIMARY KEY," + values + ")";
	        db.execSQL(CREATE_TABLE);
		}
	}

	@Override
	public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
		 // Drop older table if existed
        db.execSQL("DROP TABLE IF EXISTS " + tableName);
        // Create tables again
        onCreate(db);
		
	}
	
    public void item_Add(String item, double amount, String category, Date purchased) {
        SQLiteDatabase db = this.getWritableDatabase();
        Format DF = new SimpleDateFormat("MM-dd-yyyy");
        ContentValues values = new ContentValues();
        values.put(col[0], item); // Item Name
        values.put(col[1], amount); // Amount
        values.put(col[2], category);
        values.put(col[3], DF.format(purchased));
     
        // Inserting Row
        db.insert(tableName, null, values);
        db.close(); // Closing database connection
    }
	
    public void settings_Edit(String setting, String value) {
        SQLiteDatabase db = this.getWritableDatabase();

        ContentValues values = new ContentValues();
        values.put(col[0], setting); // Setting
        values.put(col[1], value); // Value
     
        //db.update(tableName, values, "ID "+"= "+1, null);
        
        // Inserting Row
        db.insert(tableName, null, values);
        db.close(); // Closing database connection
    }
    
    public void category_Add(String category){
    	SQLiteDatabase db = this.getWritableDatabase();
    	ContentValues values = new ContentValues();
    	values.put(col[0], category);
    	 // Inserting Row
    	db.insert(tableName, null, values);
        db.close(); // Closing database connection
    }
    
    public void category_Add(String[] category){
    	SQLiteDatabase db = this.getWritableDatabase();
    	ContentValues values = new ContentValues();
    	for (String cat : category){
    		values.put(col[0], cat);
	   	 	// Inserting Row
    		//db.update(tableName, values, "_id "+"="+1, null);
    		db.insert(tableName, null, values);
	    }
        db.close(); // Closing database connection
    }
    
    public List<String> getValues_1_categories(){
    	List<String> result = new ArrayList<String>();
    	SQLiteDatabase db = this.getWritableDatabase();
    	
    	String Query = "SELECT  * FROM " + tableName;
    	
        Cursor cursor = db.rawQuery(Query, null);
     
        if (cursor.moveToFirst()) {
            do {
                result.add(cursor.getString(1));
            } while (cursor.moveToNext());
        }
        cursor.close();
        return result;
    }
    public Pair<List<String>, List<String>> getValues_2_settings(){
    	List<String> item = new  ArrayList<String>(); List<String> value = new  ArrayList<String>();
    	SQLiteDatabase db = this.getWritableDatabase();
    	
    	String Query = "SELECT  * FROM " + tableName;
    	
        Cursor cursor = db.rawQuery(Query, null);
     
        if (cursor.moveToFirst()) {
            do {
            	value.add(cursor.getString(0));
                item.add(cursor.getString(1));
            } while (cursor.moveToNext());
        }
        cursor.close();
        return new Pair<List<String>, List<String>>(item, value);
    		
    	
    }
}
