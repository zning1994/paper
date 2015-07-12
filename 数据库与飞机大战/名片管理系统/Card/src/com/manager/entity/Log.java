package com.manager.entity;

import java.util.Date;

public class Log {
	private int LogId;
	private String UsersName;
	private String CardName;
	private String GroupName;
	private Date Date;
	private String Action;
	public int getLogId() {
		return LogId;
	}
	public void setLogId(int logId) {
		LogId = logId;
	}
	public String getUsersName() {
		return UsersName;
	}
	public void setUsersName(String usersName) {
		UsersName = usersName;
	}
	public String getCardName() {
		return CardName;
	}
	public void setCardName(String cardName) {
		CardName = cardName;
	}
	public String getGroupName() {
		return GroupName;
	}
	public void setGroupName(String groupName) {
		GroupName = groupName;
	}
	public Date getDate() {
		return Date;
	}
	public void setDate(Date date) {
		Date = date;
	}
	public String getAction() {
		return Action;
	}
	public void setAction(String action) {
		Action = action;
	}
}
