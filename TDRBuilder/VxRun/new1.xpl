<?xml version = "1.0" ?><!-- /*Begin Test*/ --><xpl version = "1.0">
<module name = "new1" date = "Fri Feb 25 00:00:18 2005
">
<entry>
<input>
<variable type = "float" name = "iv1" default_value = "2.800000"/>
<variable type = "boolean" name = "iv2" default_value = "false"/>
</input></entry><initialize>
<next id = "0"/>
<global>
<array name = "gv1" element_type = "float" array_size = "5">
<arrayelement index = "0" default_value = "0.000000e+000"/>
<arrayelement index = "1" default_value = "-1.000000"/>
<arrayelement index = "2" default_value = "0.000000e+000"/>
<arrayelement index = "3" default_value = "0.000000e+000"/>
<arrayelement index = "4" default_value = "1.000000"/>
</array><variable type = "integer" name = "gv2" default_value = "34"/>
<variable type = "boolean" name = "gv3" default_value = "false"/>
<variable type = "byte" name = "gv4" default_value = "0"/>


</global><local>
<array name = "lv1" element_type = "byte" array_size = "6">
<arrayelement index = "0" default_value = "0"/>
<arrayelement index = "1" default_value = "1"/>
<arrayelement index = "2" default_value = "0"/>
<arrayelement index = "3" default_value = "0"/>
<arrayelement index = "4" default_value = "0"/>
<arrayelement index = "5" default_value = "1"/>
</array><variable type = "integer" name = "lv2" default_value = "0"/>


</local></initialize><processor name = "Porcessor" id = "0" type = "3">
<previous id = "-3"/>
<next id = "1"/>
<method>
<![CDATA[
long Porcessor0(void)
{
	iv1 =  2+4;
	gv2 =  iv1+3;
	m_nRegister = 1;
	return m_nRegister;
}]]>
</method>

</processor><processor name = "?" id = "1" type = "5">
<previous id = "0"/>
<next_if_true id = "3"/>
<next_if_false id = "2"/>
<method>
<![CDATA[
long Compare(void)
{
	boolean  bCmp;
	bCmp = (gv2==3 || iv2==true && gv4!=3.7);


	if (bCmp)
	{
		m_nRegister = 3;
	}
	else
	{
		m_nRegister = 2;
	}


	return m_nRegister;
}]]>
</method>

</processor><processor name = "Porcessor" id = "2" type = "3">
<previous id = "1"/>
<next id = "-4"/>
<method>
<![CDATA[
long Porcessor2(void)
{
	gv4 =  3;
	gv3 =  true;
	m_nRegister = -4;
	return m_nRegister;
}]]>
</method>

</processor><processor name = "Porcessor" id = "3" type = "3">
<previous id = "1"/>
<next id = "-4"/>
<method>
<![CDATA[
long Porcessor3(void)
{
	iv2 =  false;
	gv3 =  true;
	m_nRegister = -4;
	return m_nRegister;
}]]>
</method>

</processor></module></xpl><!-- /*End Test*/ -->