/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package conexion_mongo;
import com.mongodb.BasicDBObject;
import com.mongodb.DB;
import com.mongodb.DBCollection;
import com.mongodb.DBCursor;
import com.mongodb.Mongo;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.net.UnknownHostException;
import java.io.File;
import java.io.FileWriter;
import java.util. *;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.io.File;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
/**
 *
 * @author hp
 */
public class Conexion_mongo {
private String español;
private String ingles;
public DB db;
public DBCollection tabla;
public DBCursor cursor;
public File archivo;
    /**
     * @param args the command line arguments
     */
public Conexion_mongo(){
    
}
        public static void main(String[] args) throws IOException {
            
            String archivo;
            archivo="D:\\file.txt";
            Conexion_mongo obj=new Conexion_mongo();
            
            String cadena;
            FileReader f = new FileReader(archivo);

            BufferedReader b = new BufferedReader(f);
            while((cadena = b.readLine())!=null) {
                System.out.println(cadena);
                obj.español=cadena;

            }
        
            b.close();
            /*String archivo1;
            archivo1="D:\\archivo.txt";
           
            String cadena1;
            FileReader f1 = new FileReader(archivo1);

            BufferedReader b1 = new BufferedReader(f1);
            while((cadena1 = b1.readLine())!=null) {
                System.out.println(cadena1);
                obj.ingles=cadena1;
            }
        
            b.close();*/
            
            try {
        Mongo mongo=new Mongo("localhost",27017);
        obj.db=mongo.getDB("polaca");
        obj.tabla=obj.db.getCollection("tablaVoc");
        
    } catch (UnknownHostException ex) {
        Logger.getLogger(Conexion_mongo.class.getName()).log(Level.SEVERE, null, ex);
    }
            //muestraContenido("C:\\Users\\hp\\Desktop\\hola.txt");
            //muestraContenido("C:\\Users\\hp\\Desktop\\chao.txt");
            System.out.println("cadena1: "+obj.español);
            //System.out.println("cadena1: "+obj.ingles);
            BasicDBObject documento=new BasicDBObject();
            documento.put("Polaca", "'"+obj.español+"'");
           // documento.put("INGLES", "'"+obj.ingles+"'");
            obj.tabla.insert(documento);
            obj.cursor=obj.tabla.find();
            String datos;
       
            while(obj.cursor.hasNext())
            {
                System.out.println("datos: "+obj.cursor.next());
            }
            //CREACION FICHERO BASE DE DATOS
            /*datos=""+obj.cursor.next();//TRANSFORMA A STRING
            //saludo=obj.tabla.find();

            try
            {
            obj.archivo = new File("C:\\Traductor\\BASEDATOS.txt");
            FileWriter escribir=new FileWriter(archivo,true);
                
                escribir.write(datos);
                
            //Cerramos la conexion
            escribir.close();
            }

            //Si existe un problema al escribir cae aqui
            catch(Exception e)
            {
            System.out.println("Error al escribir");
            
            }*/
        }
}

    
    