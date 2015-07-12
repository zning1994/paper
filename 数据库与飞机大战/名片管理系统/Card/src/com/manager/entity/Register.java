package com.manager.entity;

public class Register {
	private int registerId;
	private String registerName;
	private String registerPassword;
	private String registerEmail;
	private int registerCompanyId;
	private int registerDepartmentId;
	private int registerPositionId;
	public int getRegisterId() {
		return registerId;
	}
	public void setRegisterId(int registerId) {
		this.registerId = registerId;
	}
	public String getRegisterName() {
		return registerName;
	}
	public void setRegisterName(String registerName) {
		this.registerName = registerName;
	}
	public String getRegisterEmail() {
		return registerEmail;
	}
	public void setRegisterEmail(String registerEmail) {
		this.registerEmail = registerEmail;
	}
	public int getRegisterCompanyId() {
		return registerCompanyId;
	}
	public void setRegisterCompanyId(int registerCompanyId) {
		this.registerCompanyId = registerCompanyId;
	}
	public int getRegisterDepartmentId() {
		return registerDepartmentId;
	}
	public void setRegisterDepartmentId(int regsiterDepartmentId) {
		this.registerDepartmentId = regsiterDepartmentId;
	}
	public int getRegisterPositionId() {
		return registerPositionId;
	}
	public void setRegisterPositionId(int registerPositionId) {
		this.registerPositionId = registerPositionId;
	}
	public String getRegisterPassword() {
		return registerPassword;
	}
	public void setRegisterPassword(String registerPassword) {
		this.registerPassword = registerPassword;
	}
	
}
