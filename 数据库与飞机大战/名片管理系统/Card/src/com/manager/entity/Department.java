package com.manager.entity;

public class Department {
	private int DepartmentId;
	private int CompanyId;
	private String DepartmentName;
	private String DepartmentTel;

	public int getDepartmentId() {
		return DepartmentId;
	}

	public void setDepartmentId(int departmentId) {
		DepartmentId = departmentId;
	}

	public int getCompanyId() {
		return CompanyId;
	}

	public void setCompanyId(int companyId) {
		CompanyId = companyId;
	}

	public String getDepartmentName() {
		return DepartmentName;
	}

	public void setDepartmentName(String departmentName) {
		DepartmentName = departmentName;
	}

	public String getDepartmentTel() {
		return DepartmentTel;
	}

	public void setDepartmentTel(String departmentTel) {
		DepartmentTel = departmentTel;
	}
}
