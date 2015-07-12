package com.manager.entity;

import java.util.Date;


public class Collect {
	private int CollectionId;
	private int CardId;
	private int UsersId;
	private Date CollectionDate;
	private String Notes;
	public int getCollectionId() {
		return CollectionId;
	}
	public void setCollectionId(int collectionId) {
		CollectionId = collectionId;
	}
	public int getCardId() {
		return CardId;
	}
	public void setCardId(int cardId) {
		CardId = cardId;
	}
	public int getUsersId() {
		return UsersId;
	}
	public void setUsersId(int usersId) {
		UsersId = usersId;
	}
	public Date getCollectionDate() {
		return CollectionDate;
	}
	public void setCollectionDate(Date collectionDate) {
		CollectionDate = collectionDate;
	}
	public String getNotes() {
		return Notes;
	}
	public void setNotes(String notes) {
		Notes = notes;
	}
	
}
