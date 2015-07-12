package com.manager.entity;

public class Company {
	private int CompanyId;
	private String CompanyName;
	private String Address;
	private String Tel;
	private String Fax;
	public int getCompanyId() {
		return CompanyId;
	}
	public void setCompanyId(int companyId) {
		CompanyId = companyId;
	}
	public String getCompanyName() {
		return CompanyName;
	}
	public void setCompanyName(String companyName) {
		CompanyName = companyName;
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
	public String getFax() {
		return Fax;
	}
	public void setFax(String fax) {
		Fax = fax;
	}
}
