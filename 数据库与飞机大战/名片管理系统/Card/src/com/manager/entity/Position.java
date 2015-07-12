package com.manager.entity;

public class Position {
	private int PositionId;
	private int DepartmentId;
	private int CompanyId;
	private String PositionName;
	private int PowerId;
	public int getPositionId() {
		return PositionId;
	}
	public void setPositionId(int positionId) {
		PositionId = positionId;
	}
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
	public String getPositionName() {
		return PositionName;
	}
	public void setPositionName(String positionName) {
		PositionName = positionName;
	}
	public int getPowerId() {
		return PowerId;
	}
	public void setPowerId(int powerId) {
		PowerId = powerId;
	}

}
