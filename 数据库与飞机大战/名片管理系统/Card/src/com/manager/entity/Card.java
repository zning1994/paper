package com.manager.entity;

import java.util.Date;
public class Card {
	private int CardId;
	private String Notes;
	private int State;
	private String Front;
	private String Behind;
	private Date CreateTime;
	public int getCardId() {
		return CardId;
	}
	public void setCardId(int cardId) {
		CardId = cardId;
	}
	public String getNotes() {
		return Notes;
	}
	public void setNotes(String notes) {
		Notes = notes;
	}
	public int getState() {
		return State;
	}
	public void setState(int state) {
		State = state;
	}
	public String getFront() {
		return Front;
	}
	public void setFront(String front) {
		Front = front;
	}
	public String getBehind() {
		return Behind;
	}
	public void setBehind(String behind) {
		Behind = behind;
	}
	public Date getCreateTime() {
		return CreateTime;
	}
	public void setCreateTime(Date createTime) {
		CreateTime = createTime;
	}
}
