<?xml version = "1.0" ?><!-- /*Begin Test*/ --><xpl version = "1.0">
<module name = "factorial" date = "Tue Mar 22 11:06:12 2005
">
<entry>
<input>
<variable type = "integer" name = "iv1" default_value = "0"/>
<variable type = "byte" name = "iv2" default_value = "0"/>
<variable type = "float" name = "iv3" default_value = "0.000000e+000"/>
<variable type = "float" name = "iv4" default_value = "0.000000e+000"/>
</input></entry><initialize>
<next id = "0"/>
<global>
<variable type = "integer" name = "gv1" default_value = "0"/>
<variable type = "byte" name = "gv2" default_value = "0"/>
<variable type = "float" name = "gv3" default_value = "0.000000e+000"/>
<variable type = "float" name = "gv4" default_value = "0.000000e+000"/>


</global><local/>
</initialize><processor name = "Processor" id = "0" type = "3">
<previous id = "-3"/>
<next id = "-4"/>
<method>
<![CDATA[
long Processor(void)
{
	iv1 =  4;
	gv1 = iv1!;
	iv2 =  17;
	gv2 = iv2!;
	iv3 = 9.876;
	gv3 = iv3!;
	iv4 = 4.321;
	gv4 = iv4!;
	m_nRegister = -4;
	return m_nRegister;
}]]>
</method>

</processor></module></xpl><!-- /*End Test*/ -->