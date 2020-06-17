var instance_skel = require('../../instance_skel');
var debug;
var log;

function instance(system, id, config) {
	var self = this;

	// super-constructor
	instance_skel.apply(this, arguments);

	self.actions(); // export actions

	return self;
}

instance.prototype.updateConfig = function(config) {
	var self = this;

	self.config = config;

	self.actions();
}

instance.prototype.init = function() {
	var self = this;

	self.status(self.STATE_OK);

	debug = self.debug;
	log = self.log;
}

// Return config fields for web config
instance.prototype.config_fields = function () {
	var self = this;
	return [
	{
		type: 'text',
		id: 'info',
		width: 12,
		label: 'Information',
		value: 'Arduino Relay (or other use cases) module. See included .ino file to load into arduino. Port 80.'
	},
	{
		type: 'textinput',
		id: 'prefix',
		label: 'URL',
		width: 12
	}
	]
}

// When module gets deleted
instance.prototype.destroy = function() {
	var self = this;
	debug("destroy");
}

instance.prototype.actions = function(system) {
	var self = this;

		self.setActions({
			'OPEN': {
				label: 'OPEN',
				options: [
				{
					type: 'dropdown',
					label: "Relay",
					id: 'command',
					default: '0',
					choices: [
					{ id: '0', label: '0 (A0)'},
					{ id: '1', label: '1 (A1)'},
					{ id: '2', label: '2 (A2)'},
					{ id: '3', label: '3 (A3)'},
					{ id: '4', label: '4 (A4)'},
					{ id: '5', label: '5 (A5)'},
					{ id: '6', label: '6 (A6)'},
					{ id: '7', label: '7 (A7)'}
					]
				}
				]
			},

			'CLOSE': {
				label: 'CLOSE',
				options: [
				{
					type: 'dropdown',
					label: "Relay",
					id: 'command',
					default: '0',
					choices: [
					{ id: '0', label: '0 (A0)'},
					{ id: '1', label: '1 (A1)'},
					{ id: '2', label: '2 (A2)'},
					{ id: '3', label: '3 (A3)'},
					{ id: '4', label: '4 (A4)'},
					{ id: '5', label: '5 (A5)'},
					{ id: '6', label: '6 (A6)'},
					{ id: '7', label: '7 (A7)'}
					]
				}
				]
			},

			'MULTI': {
				label: 'MULTI',
				options: [
				{
					type: 'textinput',
					label: "Command (ex: 0=1&1=0&2=0)",
					id: 'command',
					default: '',
				}
				]
			}
		});
	
}
instance.prototype.action = function(action) {
	var self = this;
	var id = action.action;
	var opt = action.options.command;
	var cmd;

	switch (id) {
		case 'OPEN':
		cmd = self.config.prefix + "/&" + opt + "=1&";
		break;
		case 'CLOSE':
		cmd = self.config.prefix + "/&" + opt + "=0&";
		break;
		case 'MULTI':
		cmd = self.config.prefix + "/&" + opt + "&";
		break;
	}

		self.system.emit('rest_get', cmd, function (err, result) {
			if (err !== null) {
				self.log('error', 'HTTP GET Request failed (' + result.error.code + ')');
				self.status(self.STATUS_ERROR, result.error.code);
			}
			else {
				self.status(self.STATUS_OK);
			}
		});
};
instance_skel.extendedBy(instance);
exports = module.exports = instance;
