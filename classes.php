<?php 
class solarSystem {
	
		protected var $name; 
		protected var $mass;
		protected var $sector;
		
		function __construct($_name, $_mass, $_sector) {
			$this->$name = $_name;
			$this->$mass = $_mass;
			$this->$sector = $_sector;
		}
		
		public function setName($_name) {
			$this->$name = $_name;
		}
		
		public function retName() {
			return $name;
		}
		
		public function setSector($_sector) {
			$this->$sector = $_sector;
		}
		
		public function retSector() {
			return $sector;
		}
		
		public function setMass($_mass) {
			$this->$mass = $_mass;
		}
		
		public function retMass() {
			return $mass;
		}
	}
	
	class planet extends solarSystem {
	
		protected var $spotNumber; //порядок в солн. системе
		protected var $orbitalPeriod;
		protected var $natSatellites;
		protected var $axisTilt; //наклон оси вращения 
		protected var $diameter;
		protected var $temperature;
		
		function printPlanet() {
			echo "Name: $this->retName(); Mass: $this->retMass(); Sector: $this->retSector(); <br>
				Spot: $this->$spotNumber; Orbital period: $this->$orbitalPeriod; Natural satellites: $this->$natSatellites; <br>
				Tilt of axis: $this->$axisTilt; Diameter: $this->$diameter; Temperature: $this->$temperature. <br>
				---------------------------------------- <br>";	
		}
		function __construct($val1, $val2, $val3, 
			$_spot, $_orbit, $_satellite, $_axis, 
				$_dia, $_temperature) {
					parent:__construct($val1,$val2,$val3);
					$this->$spotNumber = $_spot;
					$this->$orbitalPeriod = $_orbit;
					$this->$natSatellites = $_satellite;
					$this->$axisTilt = $_axis;
					$this->$diameter = $_dia;
					$this->$temperature = $_temperature;
		}
		
		public function setSpot($_spot) {
			$this->$spotNumber = $_spot;
		}
		
		public function retSpot() {
			return $spotNumber;
		}
		
		public function setOrbitalPeriod($_period) {
			$this->$orbitalPeriod = $_period;
		}
		
		public function retOrbitalPeriod() {
			return >$orbitalPeriod;
		}
		
		public function setNatSatellites($_satellite) {
			$this->$natSatellites = $_satellite;
		}
		
		public function retNatSatellites() {
			return $natSatellites;
		}
		
		public function setAxisTilt($_axis) {
			$this->$axisTilt = $_axis;
		}
		
		public function retAxisTilt() {
			return $axisTilt;
		}	
		
		public function setDiameter($_dia) {
			$this->$diameter = $_dia;
		}
		
		public function retDiameter() {
			return $diameter;
		}
		
		public function setTemp($_temp) {
			$this->$temperature = $_temp;
		}
		
		public function retTemp() {
			return $temperature;
		}
	}
	
	class star extends solarSystem {
	
		private var $catalogueNum;
		private var $diameter;
		private var $temperature;
		
		function __construct($val1, $val2, $val3, 
			$_num, $_dia, $_temperature) {
				parent:__construct($val1,$val2,$val3);
				$this->$catalogueNum = $_num;
				$this->$diameter = $_dia;
				$this->$temperature = $_temperature;
		}
		
		public function setCatNum($_num) {
			$this->$catalogueNum = $_num;
		}
		
		public function retCatNum() {
			return $catalogueNum;
		}
		
		public function setDiameter($_dia) {
			$this->$diameter = $_dia;
		}
		
		public function retDiameter() {
			return $diameter;
		}
		
		public function setTemp($_temp) {
			$this->$temperature = $_temp;
		}
		
		public function retTemp() {
			return $temperature;
		}
	}
	
	class satellite extends planet {
	
	private var $catalogueName;
	
	function proportion($planet) {
		if($this->$spotNumber != $planet->retSpot()) {
			echo "$this->name is not a satellite of $planet->retName(). <br>";
			return -1;
		} else {
			return ($this->diameter/$planet->retDiameter());
		}
	}
	
	function __construct($val1, $val2, $val3, 
			$_spot, $_orbit, $_satellite, $_axis, 
				$_dia, $_temperature, $_catName) {
					parent:__construct($val1,$val2,$val3,
						$_spot, $_orbit, $_satellite,
						$_axis, $_dia, $_temperature);
					$this->$catalogueName = $_catName;
		}
	
	function setCatalogueName($val) {
		$this->$catalogueName = $val;
	}
	
	function retCatalogueName() {
		return $catalogueName;
	}
	
	
class solarSystemCollection
	{
		private $elements = array (
			"planets" => $planets[],
			"stars" => $stars[],
			"satellites" => $satellites[],
		);
		
		public function add($element, $key)
		{
			if($key != "planets" || $key != "stars"
				|| $key != "satellites") {
				echo "The key is wrong! <br>";
			} else {
				$this->$elements[$key] = $element;
			}
		}
		
		public function showPlanets() {
			foreach($elements["planets"] as $value) {
				$value->printPlanet();
			}
		}
		
	} 
	?>