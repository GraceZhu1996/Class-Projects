package com.salakotolu.restaurant;


import android.app.Fragment;
import android.content.Context;
import android.graphics.Color;
import android.graphics.Typeface;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.LinearLayout;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;
import android.widget.Toast;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

import java.text.NumberFormat;
import java.util.HashMap;
import java.util.Map;


/**
 * A simple {@link Fragment} subclass.
 *
 */
public class menu_page extends Fragment {


    public menu_page() {
        // Required empty public constructor

    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        // Inflate the layout for this fragment
        View view = inflater.inflate(R.layout.fragment_menu_page, container, false);

        FrameLayout base = (FrameLayout) view.findViewById(R.id.fragment_base);

        base.addView(newTable(Data.drawer_position, view.getContext()));

        return view;
    }



    public static TableLayout newTable(int position, final Context context){
        String sectionTitle = Data.drawer_names[position];
        JSONArray Menu = Data.menus.get(sectionTitle);

        TableLayout table = new TableLayout(context);
        table.setBackgroundColor(Color.TRANSPARENT);
        table.setStretchAllColumns(true);
        table.setShrinkAllColumns(true);
        table.setShowDividers(LinearLayout.SHOW_DIVIDER_MIDDLE);


        NumberFormat currency = NumberFormat.getCurrencyInstance();
        for (Object item_ob : Menu){
            JSONObject i = (JSONObject) item_ob;


            LinearLayout menu_item = new LinearLayout(context);
            menu_item.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT));
            menu_item.setOrientation(LinearLayout.HORIZONTAL);
            //menu_item.setBackgroundColor(Color.BLACK);
            menu_item.setPadding(2, 0, 2, 0);

            Button add = new Button(context);
            add.setBackgroundResource(R.drawable.rounded_with_image);
            add.setLayoutParams(new TableRow.LayoutParams(TableRow.LayoutParams.WRAP_CONTENT, TableRow.LayoutParams.WRAP_CONTENT));
            add.setHighlightColor(Color.GREEN);
            add.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {

                    if (!runtime_Data.hint_showed) {
                        Toast.makeText(context, "Hold to customize this order.", Toast.LENGTH_LONG).show();
                        runtime_Data.hint_showed = true;
                    }
                    int tag = Integer.parseInt(v.getTag().toString());
                    Map<String, String> order = Data.items.get(tag);

                    boolean notfound = true;
                    for (Map<String, String> item : Data.tray){
                        //Check if item in in tray
                        String item_tag = item.get("tag");
                        String view_tag = v.getTag().toString();
                        if (item_tag.equals(view_tag)){
                            //If the item is in the tray, just update its quantity
                            Data.tray.remove(item);
                            int quantity = Integer.parseInt(item.get("quantity"));
                            item.put("quantity", String.valueOf(quantity+1));
                            Data.tray.add(item);
                            notfound = false;
                            break;
                        }
                    }
                    if (notfound){
                        //If the item is not on the list
                        order.put("quantity", "1");
                        Data.tray.add(order);
                    }

                    // updateTray(context);

                }
            });
            menu_item.addView(add);


            LinearLayout contain = new LinearLayout(context);
            contain.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT));
            contain.setOrientation(LinearLayout.VERTICAL);
            contain.setBackgroundColor(Color.TRANSPARENT);
            contain.setPadding(3, 0, 0, 0);

            LinearLayout menu = new LinearLayout(context);
            menu.setOrientation(LinearLayout.HORIZONTAL);
            menu.setGravity(Gravity.CENTER_HORIZONTAL);

            String name = (i.get("name").toString());
            String price = (i.get("price").toString());
            String item_description = (i.get("description").toString());
            int tag = Integer.parseInt(i.get("ID").toString());

            TextView item = new TextView(context);
            item.setText(name);
            item.setGravity(Gravity.LEFT);
            item.setPadding(3, 0, 0, 0);
            item.setTextSize(20);
            item.setTypeface(Typeface.DEFAULT_BOLD);
            item.setMaxLines(1);
            item.setEllipsize(TextUtils.TruncateAt.END);
            //item.setTextColor(Color.BLACK);
            item.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT, 1f));

            TextView amount = new TextView(context);
            amount.setText(currency.format(Double.valueOf(price)));
            amount.setTextSize(20);
            amount.setTypeface(Typeface.DEFAULT_BOLD);
            amount.setMaxLines(1);
            amount.setEllipsize(TextUtils.TruncateAt.END);
            amount.setGravity(Gravity.RIGHT);
            amount.setPadding(0, 0, 3, 0);
            //amount.setTextColor(Color.BLACK);
            amount.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT, 1f));

            Map<String, String> itemsMap = new HashMap<String, String>();
            itemsMap.put("name", name);
            itemsMap.put("price", price);
            itemsMap.put("description", item_description);
            itemsMap.put("tag", String.valueOf(tag));

            add.setTag(tag);
            Data.items.put(tag, itemsMap);

            menu.addView(item);
            menu.addView(amount);
            menu.setPadding(0, 5, 0, 5);

            contain.addView(menu);

            menu_item.addView(contain);

            if (item_description != "" && item_description!= null){
                TextView description = new TextView(context);
                description.setText(item_description);
                description.setTextSize(11);
                description.setTypeface(Typeface.defaultFromStyle(Typeface.ITALIC));
                description.setEllipsize(TextUtils.TruncateAt.END);
                description.setTextColor(Color.WHITE);
                description.setBackgroundColor(Color.TRANSPARENT);
                description.setPadding(5, 0, 0, 0);
                contain.addView(description);
            }
            try{
                if(Data.items.size() % 2 == 0){
                    menu_item.getBackground().setAlpha(70);
                }else{
                    menu_item.getBackground().setAlpha(50);
                }
            }catch (Exception e){

            }

            table.addView(menu_item);
        }
        return table;
    }



}
