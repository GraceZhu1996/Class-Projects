package com.salakotolu.walletview;

import android.app.Application;


public class WalletView extends Application {
	private Data data = new Data(this);
	private boolean FirstRun = true;
	
	public Data GetData(){
		return data;
	}
	
	public void updateData(Data d){
		data = d;
	}
}
