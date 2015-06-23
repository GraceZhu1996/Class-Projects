package com.salakotolu.restaurant;

import android.content.Context;
import android.os.Environment;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;

import java.io.FileReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

/**
 * Created by creed on 7/29/14.
 */
public class Data {

    public static Map<String, JSONArray> menus = new HashMap<String, JSONArray>();
    public static String[] drawer_names;
    public static Map<Integer, Map<String, String>> items;

    static {
        items = new HashMap<Integer, Map<String, String>>();
    }

    public static List<Map<String, String>> tray = new ArrayList<Map<String, String>>();
    public static int drawer_position;

    public static Context context;

    public void onStart(Context c) throws  Exception{
        context = c;
            JSON();
    }
    void JSON() throws Exception {
        JSONParser parser = new JSONParser();

            JSONObject menu_file = (JSONObject) parser.parse(new FileReader(Environment.getExternalStorageDirectory()+ "/Download//test.json"));
            Set<String> menukeys =  menu_file.keySet();

            for (String o : menukeys) {
                JSONArray item = (JSONArray) menu_file.get(o);
                menus.put(o, item);
            }
            drawer_names = menukeys.toArray(new String[menukeys.size()]);
    }


}