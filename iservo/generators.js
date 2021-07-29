Blockly.JavaScript['iservo'] = function(block) {
	var dropdown_pin = block.getFieldValue('pin');
	var value_angle = Blockly.JavaScript.valueToCode(block, 'angle', Blockly.JavaScript.ORDER_ATOMIC);
	// TODO: Assemble JavaScript into code variable.
	var code = 'DEV_I2C1.iSERVO(0, 0x40).setAngle(' + dropdown_pin + ', ' + value_angle + ');\n';
	return code;
};

Blockly.JavaScript['iservo_calibrate'] = function(block) {
	var dropdown_pin = block.getFieldValue('pin');
	var number_min = block.getFieldValue('min');
	var number_max = block.getFieldValue('max');
	// TODO: Assemble JavaScript into code variable.
	var code = 'DEV_I2C1.iSERVO(0, 0x40).calibrate(' + dropdown_pin + ', ' + number_min + ', ' + number_max + ');\n';
	return code;
};