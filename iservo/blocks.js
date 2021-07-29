Blockly.Blocks['iservo'] = {
	init: function() {
		this.appendValueInput("angle")
			.setCheck("Number")
			.appendField(Blockly.Msg.MYSERVO["Servo pin"])
			.appendField(new Blockly.FieldDropdown([
				["0","0"],
				["1","1"],
				["2","2"],
				["3","3"],
				["4","4"],
				["5","5"],
				["6","6"],
				["7","7"],
				["8","8"],
				["9","9"],
				["10","10"],
				["11","11"],
				["12","12"],
				["13","13"],
				["14","14"],
				["15","15"],
			]), "pin")
			.appendField(Blockly.Msg.MYSERVO["set angle to"]);
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(105);
		this.setTooltip(Blockly.Msg.MYSERVO["Give angle to your servo motor"]);
		this.setHelpUrl("https://www.ioxhop.com/");
	},
	xmlToolbox: function() {
		return `
			<block type="iservo">
				<value name="angle">
					<shadow type="math_number">
						<field name="VALUE">90</field>
					</shadow>
				</value>
			</block>
		`;
	}
};

Blockly.Blocks['iservo_calibrate'] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.MYSERVO["Servo pin"])
			.appendField(new Blockly.FieldDropdown([
				["0","0"],
				["1","1"],
				["2","2"],
				["3","3"],
				["4","4"],
				["5","5"],
				["6","6"],
				["7","7"],
				["8","8"],
				["9","9"],
				["10","10"],
				["11","11"],
				["12","12"],
				["13","13"],
				["14","14"],
				["15","15"],
			]), "pin")
			.appendField(Blockly.Msg.MYSERVO["calibrate time to"] + " (")
			.appendField(new Blockly.FieldNumber(0.5, 0, 20), "min")
			.appendField(",")
			.appendField(new Blockly.FieldNumber(2.5, 0, 20), "max")
			.appendField(")");
		this.setInputsInline(false);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(105);
		this.setTooltip(Blockly.Msg.MYSERVO["Calibration your servo motor"]);
		this.setHelpUrl("https://www.ioxhop.com/");
	}
};