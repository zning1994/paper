package com.manager.entity;

public class Card_Users {
	private int CardId;
	private String CardUsersName;
	private String Address;
	private String Tel;
	private String Email;
	private int PostCode;
	private int CompanyId;
	private int DepartmentId;
	private int PositionId;


	public int getCardId() {
		return CardId;
	}

	public void setCardId(int cardId) {
		CardId = cardId;
	}

	public String getCardUsersName() {
		return CardUsersName;
	}

	public void setCardUsersName(String cardUsersName) {
		CardUsersName = cardUsersName;
	}

	public String getAddress() {
		return Address;
	}

	public void setAddress(String address) {
		Address = address;
	}

	public String getTel() {
		return Tel;
	}

	public void setTel(String tel) {
		Tel = tel;
	}

	public String getEmail() {
		return Email;
	}

	public void setEmail(String email) {
		Email = email;
	}

	public int getPostCode() {
		return PostCode;
	}

	public void setPostCode(int postCode) {
		PostCode = postCode;
	}

	public int getCompanyId() {
		return CompanyId;
	}

	public void setCompanyId(int companyId) {
		CompanyId = companyId;
	}

	public int getDepartmentId() {
		return DepartmentId;
	}

	public void setDepartmentId(int departmentId) {
		DepartmentId = departmentId;
	}

	public int getPositionId() {
		return PositionId;
	}

	public void setPositionId(int positionId) {
		PositionId = positionId;
	}
}
